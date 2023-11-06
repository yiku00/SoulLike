// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatUI.h"
#include "RevanantStatUI.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKE_API URevanantStatUI : public UStatUI
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> RevolverImage_SPin;

	UPROPERTY(meta = (BindWidget), Transient)
	TObjectPtr<class UImage> CrossHair;

	UPROPERTY()
	TObjectPtr<class ARevanantCpp> OwnedRevanant; //ĳ����
private:
	UFUNCTION(BlueprintCallable)
	int GetCurrentBullet();

	UFUNCTION(BlueprintCallable)
	void PlaySpinAnim();
protected:
	virtual void NativeConstruct();
	virtual void BeginDestroy();
	virtual void NativeTick(const FGeometry& MyGeometry, float dt);

};
