// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SoulLikeCharacter.h"

#include "GunFightCharacter.h"
#include "RevanantCpp.generated.h"

/**
 * 
 */

UCLASS()
class SOULLIKE_API ARevanantCpp : public AGunFightCharacter
{
	GENERATED_BODY()
public:
	ARevanantCpp();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE uint8 GetCurrentBullet() {return 0;};

	UFUNCTION(BlueprintCallable)
	FORCEINLINE uint8 GetMaxBullet() { return 0; };
protected:
	virtual void Attack(const FInputActionValue& Value);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float delta) override;
	virtual void CheckCameraLoc(float dt) override;
	virtual void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
private:
	float FireStaminaCost;
	float AimStaminaCost;
	float EscapeStaminaBonus;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ReloadAction;

	virtual FVector GetProjecticleDirection(float RayDistance) override;
	void Aim(const FInputActionValue& Value) override;
	void AimOff(const FInputActionValue& Value) override;
	void Reload(const FInputActionValue& Value) override;

	
};
