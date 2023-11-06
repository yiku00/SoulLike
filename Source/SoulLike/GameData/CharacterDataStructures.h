// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "CharacterDataStructures.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxHp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxMp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float StaminaRecoveryRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttackStaminaCost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 MaxAttackCnt;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 CurrentAttackCount;

	FCharacterData()
	{
		MaxHp = 0;
		MaxStamina = 0;
		StaminaRecoveryRate = 0;
		AttackStaminaCost = 0;
		MaxAttackCnt = 0;
		CurrentAttackCount = 0;
	}
};

USTRUCT(BlueprintType)
struct FGunFighterData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentBulletCnt;//Optimized

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxBulletCnt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AimStaminaCost;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EscapeStaminaBonus;



	FGunFighterData()
	{
		AimStaminaCost = 0.f;
		EscapeStaminaBonus = 0.f;
		MaxBulletCnt = 0;
		CurrentBulletCnt = 0;
	}
};