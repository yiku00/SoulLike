// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SoulLikeCharacter.h"
#include "GunFightCharacter.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReloadNotifyDelegateForMainUI);

UCLASS()
class SOULLIKE_API AGunFightCharacter : public ASoulLikeCharacter
{
	GENERATED_BODY()

public:
	AGunFightCharacter();

	UPROPERTY(BlueprintAssignable)
	FOnReloadNotifyDelegateForMainUI OnReloadNotify;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isReloading; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsAiming; //use this val lead Animation Blueprint to determine this character's status, Aiming or Not
protected:
	FTransform AimingCameraTransform;
	FTransform NormalCameraTransform;
	virtual FVector GetProjecticleDirection(float RayDistance);
	virtual void Aim(const FInputActionValue& Value);
	virtual void AimOff(const FInputActionValue& Value);
	virtual void Reload(const FInputActionValue& Value);
	virtual void CheckCameraLoc(float dt);
	virtual void Tick(float delta) override;
private:

	
};
