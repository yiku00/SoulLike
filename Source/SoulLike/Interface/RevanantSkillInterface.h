// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RevanantSkillInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URevanantSkillInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SOULLIKE_API IRevanantSkillInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool GetReloadingFlag() = 0;			//retrun isReloading;
	virtual bool GetAimFlag() = 0;					//return IsAiming;
	virtual bool GetAttackFlag() = 0;				//return IsAttacking;
	virtual FVector GetSocketLocation() = 0;		//return Projecticle's Spawning Socket Location 
	virtual FVector GetPlayerAimingDirection() = 0;	//return Player's Watching Vector
	virtual FVector GetCameraLocation() = 0;		//return Camera's Location
	virtual FRotator GetPawnRotation() = 0;			//return Character's Rotation
	virtual void SetIsAttack(bool NewBool) = 0;		//Set Attack Flag
	virtual void SetIsReloading(bool NewBool) = 0;	//Set Reloading Flag
	virtual void SetIsAiming(bool NewBool) = 0;		//Set Aiming Flag
	virtual void PlayMontageFromSkill(class UAnimMontage* AnimMontage) =0; //Play Skill's Montage
	virtual UWorld* GetPawnWorld() = 0;				//Get Pawn's World to Spawn Projecticle
	virtual void FillBulletMax() = 0;				//Fill Current Bullet Count Full
};
