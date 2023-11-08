// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Blueprint/UserWidget.h>
#include "MainHUDCpp.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKE_API UMainHUDCpp : public UUserWidget
{
	GENERATED_BODY()

private:

protected:
	float OwnersMaxHp;
	float OwnersMaxMp;
	float OwnersMaxStamina;

	UPROPERTY()
	TObjectPtr<class UProgressBar> HPProgressBar;

	UPROPERTY()
	TObjectPtr<class UProgressBar> MPProgressBar;

	UPROPERTY()
	TObjectPtr<class UProgressBar> StaminaProgressBar;

public:
	UFUNCTION()
	virtual void UpdateHpPercentage(const float NewHp);

	UFUNCTION()
	virtual void UpdateMpPercentage(const float NewMp);

	UFUNCTION()
	virtual void UpdateStaminaPercentage(const float NewStamina);

	UFUNCTION()
	void SetMaxHp(const float NewHp);// { OwnersMaxHp = NewHp; };

	UFUNCTION()
	void SetMaxMp(const float NewMp);// { OwnersMaxMp = NewMp; };

	UFUNCTION()
	void SetMaxStamina(const float NewStamina);// { OwnersMaxStamina = NewStamina; };
protected:
	virtual void NativeConstruct() override;
	virtual void BeginDestroy()override;
	virtual void NativeTick(const FGeometry& MyGeometry, float dt) override;

};
