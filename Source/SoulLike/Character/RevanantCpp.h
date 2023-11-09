// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GunFightCharacter.h"
#include "Interface/RevanantSkillInterface.h"
#include "RevanantCpp.generated.h"

/**
 * 
 */

UCLASS()
class SOULLIKE_API ARevanantCpp : public AGunFightCharacter , public IRevanantSkillInterface
{

	GENERATED_BODY()
public:
	ARevanantCpp();
protected:
	virtual void Attack(const FInputActionValue& Value);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float delta) override;
	virtual void CheckCameraLoc(float dt) override;
	virtual void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

protected:
	//Revanant Skill Interface Function Override
	virtual bool GetReloadingFlag() override { return isReloading; }; //retrun isReloading;
	virtual bool GetAimFlag() override { return IsAiming; }; //IsAiming;
	virtual bool GetAttackFlag()override { return IsAttacking; };
	virtual FVector GetSocketLocation() override { return GetMesh()->GetSocketLocation(MuzzleSocketName); };		//return Projecticle's Spawning Socket Location 
	virtual FVector GetPlayerAimingDirection() override;	//return Player's Watching Vector
	virtual FVector GetCameraLocation() override;		//return Camera's Location
	virtual FRotator GetPawnRotation()override;			//return Character's Rotation
	virtual void SetIsAttack(bool NewBool) override { IsAttacking = NewBool; };		//Set Attack Flag
	virtual void SetIsReloading(bool NewBool) override { isReloading = NewBool; };	//Set Reloading Flag
	virtual void SetIsAiming(bool NewBool) override { IsAiming = NewBool; };		//Set Aiming Flag
	virtual void PlayMontageFromSkill(class UAnimMontage* AnimMontage)override;
	virtual UWorld* GetPawnWorld()override { return GetWorld(); };
	virtual void FillBulletMax() override;
private:
	float FireStaminaCost;
	float AimStaminaCost;
	float EscapeStaminaBonus;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ReloadAction;
	void Aim(const FInputActionValue& Value) override;
	void AimOff(const FInputActionValue& Value) override;
	void Reload(const FInputActionValue& Value) override;

	class USkill* BasicAttack;
	class USkill* ReloadSkill;
};
