// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SkillData.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKE_API USkillData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillData)
	float CostHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillData)
	float CostMp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillData)
	float CostStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillData)
	uint8 CostBullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillData)
	TObjectPtr<UAnimMontage> ToPlayMontage;
};
