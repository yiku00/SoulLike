// Copyright Epic Games, Inc. All Rights Reserved.

#include "SoulLikeCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include <Kismet/GameplayStatics.h>

//////////////////////////////////////////////////////////////////////////
// ASoulLikeCharacter

ASoulLikeCharacter::ASoulLikeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

void ASoulLikeCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (GetMesh() && GetMesh()->GetAnimInstance())
	{
		GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ASoulLikeCharacter::OnMontageEnded);
	}

	//Load Player Data
	CurrentBulletCnt = 4;
	MaxHp = 100;
	CurrentHp = 100;
	MaxStamina = 120;
	CurrentStamina = 120;
	StaminaRecoveryRate = 20.f;
	AimStaminaCost = 15.f;
	FireStaminaCost = 30.f;
}

void ASoulLikeCharacter::Tick(float delta)
{
	Super::Tick(delta);
	CheckCameraLoc(delta);
	TickHpLogic(delta);
	TickStaminaLogic(delta);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASoulLikeCharacter::CheckCameraLoc(float dt)
{
	FVector TargetCameraLocation = IsAiming ? AimingCameraLocation : NormalCameraLocation;
	FRotator TargetCameraRotation = IsAiming ? AimingCameraRotation : NormalCameraRotation;
	FVector DesiredOffset = IsAiming ? AimingCameraLocation : NormalCameraLocation;
	FVector NewPosition = FMath::VInterpTo(CameraBoom->SocketOffset, TargetCameraLocation, dt, 1.0);
	FRotator NewRotator = FMath::RInterpTo(FollowCamera->GetRelativeRotation(), TargetCameraRotation, dt, 10);
	

	FVector NewOffset = FMath::VInterpTo(CameraBoom->SocketOffset, DesiredOffset, dt, 5.0f);
	CameraBoom->SocketOffset = NewOffset;
	FollowCamera->SetRelativeRotation(NewRotator);
}

void ASoulLikeCharacter::TickStaminaLogic(float dt)
{
	if (CurrentStamina >= MaxStamina) {
		CurrentStamina = MaxStamina;
		return;
	}

	CurrentStamina += StaminaRecoveryRate * dt;
}

void ASoulLikeCharacter::TickHpLogic(float dt)
{

}

FVector ASoulLikeCharacter::GetProjecticleDirection(float RayDistance)
{
	FHitResult HitResult;
	FVector StartLocation = FollowCamera->GetComponentLocation();
	FVector EndLocation = StartLocation + (FollowCamera->GetForwardVector() * RayDistance);

	// 캐릭터는 무시하기 위한 Collision Query Params 설정
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	// 레이캐스팅 실행
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams);

	if (bHit)
	{
		// 레이가 무언가에 맞았다면, 그 위치로 발사체를 발사
		FVector ShootDirection = (HitResult.ImpactPoint - GetMesh()->GetSocketLocation(FName(TEXT("FX_GUN_MUZZLE")))).GetSafeNormal();
		return ShootDirection;
	}
	else {
		return (EndLocation - GetMesh()->GetSocketLocation(FName(TEXT("FX_GUN_MUZZLE")))).GetSafeNormal();
	}
	return FVector();
}


void ASoulLikeCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASoulLikeCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASoulLikeCharacter::Look);

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ASoulLikeCharacter::Fire);

		EnhancedInputComponent->BindAction(EscapeAction, ETriggerEvent::Started, this, &ASoulLikeCharacter::Escape);

		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &ASoulLikeCharacter::Aim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &ASoulLikeCharacter::AimOff);
	
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &ASoulLikeCharacter::Reload);
	}

}

void ASoulLikeCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);

		if (!(MovementVector.Y == 0 && MovementVector.X == 0)) {
			LastUpdatedDirection = ForwardDirection * MovementVector.Y + RightDirection * MovementVector.X;
			LastUpdatedDirection.Normalize();
		}
	}
}

void ASoulLikeCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASoulLikeCharacter::Fire(const FInputActionValue& Value)
{
	if (isReloading || !IsAiming)return;
	if(CurrentBulletCnt > 0 && CurrentStamina > FireStaminaCost)
	{

		IsAttacking = true;

		if (FireAnimMontage) {
			PlayAnimMontage(FireAnimMontage);
		}

		CurrentBulletCnt--;
		CurrentStamina -= FireStaminaCost;
		if (CurrentStamina <= 0)CurrentStamina = 0.f;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AProjecticle* FiredObj =
			GetWorld()->SpawnActor<AProjecticle>(ProjecticleClass,
			GetMesh()->GetSocketLocation(FName(TEXT("FX_GUN_MUZZLE"))) + FollowCamera->GetForwardVector() * 15.f,
			GetActorRotation(), SpawnParams);


		FiredObj->FireInDirection(
			GetProjecticleDirection(FiredObj->ProjectileMovement->InitialSpeed * FiredObj->GetLifeSpan()),
			this);

	}
	else if (CurrentStamina < FireStaminaCost)
	{
		//There is no Stamina

	}
	else {
		//PlaySound Effects Empty
		if (EmptyBulletSound) {
			UGameplayStatics::PlaySoundAtLocation(this, EmptyBulletSound, GetActorLocation());
		}
	}
}

void ASoulLikeCharacter::Reload(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Reload"));
	if (CurrentBulletCnt == 4)return;
	isReloading = true;
	if (ReloadAnimMontageLong) {
		PlayAnimMontage(ReloadAnimMontageLong);
	}
	
}

void ASoulLikeCharacter::Escape(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Escape"));
}

void ASoulLikeCharacter::Aim(const FInputActionValue& Value)
{
	StaminaRecoveryRate -= AimStaminaCost;
	IsAiming = true;
	bUseControllerRotationYaw = true;
}

void ASoulLikeCharacter::AimOff(const FInputActionValue& Value)
{
	StaminaRecoveryRate += AimStaminaCost;
	IsAiming = false;
	bUseControllerRotationYaw = false;
}

FVector ASoulLikeCharacter::CalculateCrossProduct() const
{
	FVector forwardVector = GetActorForwardVector();
	FVector toTargetVector = LastUpdatedDirection.GetSafeNormal();
	return FVector::CrossProduct(forwardVector, toTargetVector);
}

float ASoulLikeCharacter::CalculateDotProduct() const
{
	FVector forwardVector = GetActorForwardVector();
	FVector toTargetVector = LastUpdatedDirection.GetSafeNormal();
	return FVector::DotProduct(forwardVector, toTargetVector);
}

void ASoulLikeCharacter::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{

	if (Montage == FireAnimMontage)
	{
		IsAttacking = false;
	}
	else if (Montage == ReloadAnimMontageLong)
	{
		isReloading = false;
		CurrentBulletCnt = 4;
	}
}
