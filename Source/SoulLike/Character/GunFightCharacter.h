// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SoulLikeCharacter.h"
#include "Interface/GunFighterInterface.h"
#include "GunFightCharacter.generated.h"

/**
 * 
 */

UCLASS()
class SOULLIKE_API AGunFightCharacter : public ASoulLikeCharacter, public IGunFighterInterface
{
	GENERATED_BODY()
public:
	AGunFightCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isReloading; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsAiming; //use this val lead Animation Blueprint to determine this character's status, Aiming or Not

	UPROPERTY()
	FName MuzzleSocketName;

protected:
	FTransform AimingCameraTransform;
	FTransform NormalCameraTransform;
	virtual FVector GetProjecticleDirection(float RayDistance);
	virtual void SetUpGunFightHUD(class UGunFighterHUD* WidgetPtr) override;
	virtual void Aim(const FInputActionValue& Value);
	virtual void AimOff(const FInputActionValue& Value);
	virtual void Reload(const FInputActionValue& Value);
	virtual void CheckCameraLoc(float dt);
	virtual void Tick(float delta) override;
	virtual void LoadCharacterData(FName InName) override;
private:

	
};
