// Copyright Epic Games, Inc. All Rights Reserved.

#include "SoulLikeCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CharacterStat/CharacterStatManager.h"
#include "UI/MainHUDCpp.h"

//////////////////////////////////////////////////////////////////////////
// ASoulLikeCharacter 

ASoulLikeCharacter::ASoulLikeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("MainCharacter"));
	GetMesh()->SetCollisionProfileName(TEXT("MainCharacterMesh"));

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

	//Init Stat Component
	StatManager = CreateDefaultSubobject<UCharacterStatManager>(TEXT("StatManager"));
}

void ASoulLikeCharacter::InitStatUI()
{
	if (HUDClass)
	{
		APlayerController* OwnerController = Cast<APlayerController>(GetController());
		UMainHUDCpp* MyWidget = CreateWidget<UMainHUDCpp>(OwnerController, HUDClass);
		if (MyWidget)
		{
			MyWidget->AddToViewport(); 
		}
		MyWidget->SetMaxHp(StatManager->GetMaxHp());
		MyWidget->SetMaxMp(StatManager->GetMaxMp());
		MyWidget->SetMaxStamina(StatManager->GetMaxStamina());

		MyWidget->UpdateHpPercentage(StatManager->GetCurrentHp());
		MyWidget->UpdateMpPercentage(StatManager->GetCurrentMp());
		MyWidget->UpdateStaminaPercentage(StatManager->GetCurrentStamina());

		StatManager->OnHpUpdatedDelegate.AddUObject(MyWidget, &UMainHUDCpp::UpdateHpPercentage);
		StatManager->OnMpUpdatedDelegate.AddUObject(MyWidget, &UMainHUDCpp::UpdateMpPercentage);
		StatManager->OnStaminaUpdatedDelegate.AddUObject(MyWidget, &UMainHUDCpp::UpdateStaminaPercentage);
	}
}

const float ASoulLikeCharacter::GetMaxHp()
{
	//StatManager->Get
	return 0.0f;
}

const float ASoulLikeCharacter::GetMaxMp()
{
	return 0.0f;
}

const float ASoulLikeCharacter::GetMaxStamina()
{
	return 0.0f;
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

	//Stat Data load
	StatManager->LoadCharacterData(CharacterName);

	//Create Stat Data Widget
	//InitStatUI();
}

void ASoulLikeCharacter::Tick(float delta)
{
	Super::Tick(delta);
	//CheckCameraLoc(delta);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASoulLikeCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASoulLikeCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASoulLikeCharacter::Look);

		EnhancedInputComponent->BindAction(EssentialAttackAction, ETriggerEvent::Started, this, &ASoulLikeCharacter::EssentialAttack);

		EnhancedInputComponent->BindAction(EscapeAction, ETriggerEvent::Started, this, &ASoulLikeCharacter::Escape);
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

void ASoulLikeCharacter::EssentialAttack(const FInputActionValue& Value)
{

}

void ASoulLikeCharacter::Escape(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Escape"));
	//if (DodgeAnimation)
	//	PlayAnimMontage(DodgeAnimation);
	//UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.1f); // 10%의 속도로 시간이 흐른다
	//CustomTimeDilation = 10.0f; // 플레이어는 원래 속도로 움직인다
	//GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed * 2;
	//StaminaRecoveryRate += EscapeStaminaBonus;
	//NSComponent->Activate();
	//NSComponent->SetCustomTimeDilation(2.0f);
}

void ASoulLikeCharacter::SetUpEssentialHUD(UMainHUDCpp* WidgetPtr)
{
	//if WidgetPtr is valid, Add Function to StatData's Delegate, 
	// and will be connected Character's Essential Data to UI

	WidgetPtr->SetMaxHp(StatManager->GetMaxHp());
	WidgetPtr->SetMaxMp(StatManager->GetMaxMp());
	WidgetPtr->SetMaxStamina(StatManager->GetMaxStamina());

	WidgetPtr->UpdateHpPercentage(StatManager->GetCurrentHp());
	WidgetPtr->UpdateMpPercentage(StatManager->GetCurrentMp());
	WidgetPtr->UpdateStaminaPercentage(StatManager->GetCurrentStamina());

	StatManager->OnHpUpdatedDelegate.AddUObject(WidgetPtr, &UMainHUDCpp::UpdateHpPercentage);
	StatManager->OnMpUpdatedDelegate.AddUObject(WidgetPtr, &UMainHUDCpp::UpdateMpPercentage);
	StatManager->OnStaminaUpdatedDelegate.AddUObject(WidgetPtr, &UMainHUDCpp::UpdateStaminaPercentage);
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

}