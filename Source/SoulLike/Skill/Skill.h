// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Skill.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExecuted);

UCLASS()
class SOULLIKE_API USkill : public UObject
{
	GENERATED_BODY()
public:
	USkill();
	FOnExecuted OnExecutedDelegate;

protected:
	UPROPERTY()
	TObjectPtr<UAnimMontage> ToPlayMontage;

	UPROPERTY()
	TObjectPtr<USoundBase> ToPlaySound;
	
	virtual void Execute();
	virtual bool CanExecute();
private:

};
