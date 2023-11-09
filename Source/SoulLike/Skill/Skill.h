// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Skill.generated.h"

/**
 * 
 */

UCLASS()
class SOULLIKE_API USkill : public UObject
{

	GENERATED_BODY()
public:
	USkill();
	//Set Owner Character's Reference As Interface
	void Initialize(class UObject* InCharacter);
	bool IsInitialiezed() { return bIsInitialiezed; }

	void SetUpAnimDelegate(FOnMontageEndedMCDelegate& Delegate);

	//Functions going to connected with StatComponent's Delegate
	FORCEINLINE void UpdateOwnerHp(float NewHp) { OwnersCurrentHp = NewHp; };
	FORCEINLINE void UpdateOwnerMp(float NewMp) { OwnersCurrentMp = NewMp; };
	FORCEINLINE void UpdateOwnerStamina(float NewStamina) { OwnersCurrentStamina = NewStamina; };
	FORCEINLINE void UpdateOwnerCurrentBullet(uint32 NewCnt) { OwnersCurrentBullet = NewCnt; };

	FORCEINLINE void UpdateOwnerMaxHp(float NewHp) { OwnersMaxHp = NewHp; };
	FORCEINLINE void UpdateOwnerMaxMp(float NewMp) { OwnersMaxMp = NewMp; };
	FORCEINLINE void UpdateOwnerMaxStamina(float NewStamina) { OwnersMaxStamina = NewStamina; };
	FORCEINLINE void UpdateOwnerMaxBullet(uint32 NewCnt) { OwnersMaxBullet = NewCnt; };

	virtual void Execute();
protected:
	UPROPERTY()
	TObjectPtr<class USkillData> SkillData;

	virtual bool CheckHasEnoughStat();

	void CostStat();

	UFUNCTION()
	virtual void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
protected:
	//Owner's Stat Data
	float OwnersMaxHp;
	float OwnersMaxMp;
	float OwnersMaxStamina;
	uint32 OwnersMaxBullet;

	float OwnersCurrentHp;
	float OwnersCurrentMp;
	float OwnersCurrentStamina;
	uint32 OwnersCurrentBullet;

	UObject* Owner;

	bool bIsInitialiezed;
};
