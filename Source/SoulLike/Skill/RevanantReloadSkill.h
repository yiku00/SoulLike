// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Skill.h"
#include "RevanantReloadSkill.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKE_API URevanantReloadSkill : public USkill
{
	GENERATED_BODY()
public:
	URevanantReloadSkill();
	virtual void Execute() override;
protected:
	virtual void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
private:
};
