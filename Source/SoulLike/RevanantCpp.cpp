// Fill out your copyright notice in the Description page of Project Settings.


#include "RevanantCpp.h"
#include "CharacterStatManager.h"
#include <EnhancedInputComponent.h>
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Projecticle.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void ARevanantCpp::Aim(const FInputActionValue& Value)
{
	StatManager->EditStaminaRoveryRate(-AimStaminaCost);
	IsAiming = true;
	bUseControllerRotationYaw = true;
}

void ARevanantCpp::AimOff(const FInputActionValue& Value)
{
	StatManager->EditStaminaRoveryRate(AimStaminaCost);
	IsAiming = false;
	bUseControllerRotationYaw = false;
}

void ARevanantCpp::Reload(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Reload"));
	if (CurrentBulletCnt == MaxBulletCnt)return;
	isReloading = true;
	if (ReloadAnimMontageLong) {
		PlayAnimMontage(ReloadAnimMontageLong);
		OnReloadNotify.Broadcast();
	}
}

void ARevanantCpp::Attack(const FInputActionValue& Value)
{
	if (isReloading || !IsAiming)return;
	if (CurrentBulletCnt > 0 && StatManager->GetStatData()->GetCurrentStamina() > FireStaminaCost)
	{

		IsAttacking = true;

		if (FireAnimMontage) {
			PlayAnimMontage(FireAnimMontage);
		}

		CurrentBulletCnt--;
		StatManager->CostStamina(FireStaminaCost);

		AProjecticle* FiredObj =
			GetWorld()->SpawnActor<AProjecticle>(ProjecticleClass,
				GetMesh()->GetSocketLocation(FName(TEXT("FX_GUN_MUZZLE"))) + FollowCamera->GetForwardVector() * 15.f,
				GetActorRotation());


		FiredObj->FireInDirection(
			GetProjecticleDirection(FiredObj->ProjectileMovement->InitialSpeed * FiredObj->GetLifeSpan()),
			this);
	}
	else if (StatManager->GetStatData()->GetCurrentStamina() < FireStaminaCost)
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

void ARevanantCpp::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &ARevanantCpp::Aim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &ARevanantCpp::AimOff);

		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &ARevanantCpp::Reload);
	}
}

void ARevanantCpp::Tick(float delta)
{
	Super::Tick(delta);

}

void ARevanantCpp::CheckCameraLoc(float dt)
{
	Super::CheckCameraLoc(dt);
	FVector TargetCameraLocation = IsAiming ? AimingCameraLocation : NormalCameraLocation;
	FRotator TargetCameraRotation = IsAiming ? AimingCameraRotation : NormalCameraRotation;
	FVector DesiredOffset = IsAiming ? AimingCameraLocation : NormalCameraLocation;
	FVector NewPosition = FMath::VInterpTo(CameraBoom->SocketOffset, TargetCameraLocation, dt, 1.0);
	FRotator NewRotator = FMath::RInterpTo(FollowCamera->GetRelativeRotation(), TargetCameraRotation, dt, 10);


	FVector NewOffset = FMath::VInterpTo(CameraBoom->SocketOffset, DesiredOffset, dt, 5.0f);
	CameraBoom->SocketOffset = NewOffset;
	FollowCamera->SetRelativeRotation(NewRotator);
}

FVector ARevanantCpp::GetProjecticleDirection(float RayDistance)
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

ARevanantCpp::ARevanantCpp()
{
	AimStaminaCost = 15.f;
	FireStaminaCost = 30.f;
	EscapeStaminaBonus = 50.f;
	MaxBulletCnt = 4;
	CurrentBulletCnt = 4;

	CharacterName = FName(TEXT("Revanant"));
}
