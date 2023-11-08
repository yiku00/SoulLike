// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BulletWidget.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKE_API UBulletWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void PlayReloadAnim();

	UFUNCTION()
	virtual void UpdateCurrentBullet(const uint32 NewBullet); //This should be called by dellegate
	
	//this function will be desinged temporary but it seems not be used
	//virtual void UpdateMaxBullet(const uint32 NewBullet); 
protected:
	virtual void NativeConstruct();

private:
	UPROPERTY()
	TObjectPtr<class UTextBlock> CurrentBulletTextBlock;

	UPROPERTY()
	TObjectPtr<class UTextBlock> MaxBulletTextBlock;

	UPROPERTY()
	TObjectPtr<UWidgetAnimation> ReloadAnim;

	UPROPERTY()
	uint32 CurrentBulletAmount;

	UPROPERTY()
	uint32 MaxBulletAmount;
};
