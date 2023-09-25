// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SoulLikeCharacter.h"
#include "MainHUDCpp.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKE_API UMainHUDCpp : public UUserWidget
{
	GENERATED_BODY()
private:
	ASoulLikeCharacter* OwningPawn;
private:
	UFUNCTION(BlueprintCallable)
	float GetOwningHp();

	UFUNCTION(BlueprintCallable)
	float GetOwningStamina();

	UFUNCTION(BlueprintCallable)
	int GetCurrentBullet();
protected:
	virtual void NativeConstruct();
public:

};
