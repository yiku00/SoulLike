// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainHUDCpp.h"
#include "StatUI.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKE_API UStatUI : public UMainHUDCpp
{
	GENERATED_BODY()
private:
	struct FCharacterData* OwnerStatData;
public:
	UFUNCTION(BlueprintCallable)
	virtual float GetOwningHp();

	UFUNCTION(BlueprintCallable)
	virtual float GetOwningStamina();

	void UpdateStat(FCharacterData* _OwnerStatData) { OwnerStatData = _OwnerStatData; };
protected:
	virtual void NativeConstruct();
	virtual void BeginDestroy();
	virtual void NativeTick(const FGeometry& MyGeometry, float dt);

};
