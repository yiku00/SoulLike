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
	class ASoulLikeCharacter* OwningPawn;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* RevolverImage_SPin;

	UPROPERTY(meta = (BindWidget), Transient)
	class UImage* CrossHair;
private:
	UFUNCTION(BlueprintCallable)
	float GetOwningHp();

	UFUNCTION(BlueprintCallable)
	float GetOwningStamina();

	UFUNCTION(BlueprintCallable)
	int GetCurrentBullet();

	UFUNCTION(BlueprintCallable)
	void PlaySpinAnim();
protected:
	virtual void NativeConstruct();
	virtual void BeginDestroy();
	virtual void NativeTick(const FGeometry& MyGeometry,float dt);
public:

};
