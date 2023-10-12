// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SoulLikeCharacter.h"
#include "RevanantCpp.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReloadNotifyDelegateForMainUI);

UCLASS()
class SOULLIKE_API ARevanantCpp : public ASoulLikeCharacter
{
	GENERATED_BODY()
private:
	int CurrentBulletCnt;//Optimized
	int MaxBulletCnt;

	float FireStaminaCost; 
	float AimStaminaCost;
	float EscapeStaminaBonus;

	const FVector AimingCameraLocation = FVector(290, 70, 90);
	const FRotator AimingCameraRotation = FRotator(0, 0, 0);

	const FVector NormalCameraLocation = FVector(0, 0, 0);
	const FRotator NormalCameraRotation = FRotator(0, 0, 0);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ReloadAction;
public:
	UPROPERTY(BlueprintAssignable)
	FOnReloadNotifyDelegateForMainUI OnReloadNotify;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isReloading;//Optimized
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsAiming;
public:
	ARevanantCpp();

	UFUNCTION(BlueprintCallable)
	int GetCurrentBullet() {return CurrentBulletCnt;};

	UFUNCTION(BlueprintCallable)
	int GetMaxBullet() { return MaxBulletCnt; };
protected:
	virtual void Aim(const FInputActionValue& Value);
	virtual void AimOff(const FInputActionValue& Value);
	virtual void Reload(const FInputActionValue& Value);
	virtual void Attack(const FInputActionValue& Value);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float delta) override;
	virtual void CheckCameraLoc(float dt);
private:
	FVector GetProjecticleDirection(float RayDistance);
};
