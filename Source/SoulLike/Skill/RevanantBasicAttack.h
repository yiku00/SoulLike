// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Skill.h"
#include "Interface/GunFighterInterface.h"
#include "RevanantBasicAttack.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKE_API URevanantBasicAttack : public USkill
{
	GENERATED_BODY()
public:
	URevanantBasicAttack(); //Unable to Use Default Constructor From Outside
	FORCEINLINE void SetReloading(const bool InReloading) {isReloading = InReloading;};
	FORCEINLINE void SetAiming(const bool InAiming) { IsAiming = InAiming; };
	virtual void Execute() override;
protected:
	bool CanExecute();

	virtual void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted) override;

private:
	FVector GetProjecticleDirection(float RayDistance);
private:
	bool isReloading;
	bool IsAiming;

	UPROPERTY()
	TSubclassOf<class AProjecticle> ProjecticleClass;

	UPROPERTY()
	TObjectPtr<class USoundBase> EmptyBulletSound;

private:

};
