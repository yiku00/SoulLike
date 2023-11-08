// Fill out your copyright notice in the Description page of Project Settings.


#include "GunFightCharacter.h"
#include "CharacterStat/CharacterStatManager.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UI/GunFighterHUD.h"

AGunFightCharacter::AGunFightCharacter()
{
	
}

FVector AGunFightCharacter::GetProjecticleDirection(float RayDistance)
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

void AGunFightCharacter::Aim(const FInputActionValue& Value)
{
	//StatManager->EditStaminaRoveryRate(-AimStaminaCost);
	IsAiming = true;
	bUseControllerRotationYaw = true;
}

void AGunFightCharacter::AimOff(const FInputActionValue& Value)
{
	//StatManager->EditStaminaRoveryRate(AimStaminaCost);
	IsAiming = false;
	bUseControllerRotationYaw = false;
}

void AGunFightCharacter::Reload(const FInputActionValue& Value)
{

}

void AGunFightCharacter::CheckCameraLoc(float dt)
{
	const FTransform TargetTransform = IsAiming ? AimingCameraTransform : NormalCameraTransform;

	FRotator NewRotator = FMath::RInterpTo(FollowCamera->GetRelativeRotation(), AimingCameraTransform.Rotator(), dt, 10);
	FVector NewOffset = FMath::VInterpTo(CameraBoom->SocketOffset, TargetTransform.GetLocation(), dt, 5.0f);

	CameraBoom->SocketOffset = NewOffset;
	FollowCamera->SetRelativeRotation(NewRotator);
}

void AGunFightCharacter::Tick(float delta)
{
	Super::Tick(delta);
	CheckCameraLoc(delta);
}

void AGunFightCharacter::SetUpGunFightHUD(UGunFighterHUD* WidgetPtr)
{
	if (WidgetPtr)
	{
		WidgetPtr->UpdateMaxBulletCnt(StatManager->GetMaxBullet());
		WidgetPtr->UpdateCurrentBulletCnt(StatManager->GetCurrentBullet());

		StatManager->OnCurrentBulletUpdated.AddUObject(WidgetPtr, &UGunFighterHUD::UpdateCurrentBulletCnt);

	}
}
