// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI/MainHUDCpp.h"
#include "SoulLikePlayerController.generated.h"

/**
 * 
 */

UENUM()
enum class AvalableKeyList : uint8 {
	Key_Q = 0,
	Key_R,
	Key_E
};

UCLASS()
class SOULLIKE_API ASoulLikePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	void SetHUDClass(TSubclassOf<UMainHUDCpp> InHUDClass);
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY()
	UMainHUDCpp* MainHUD;
	TSubclassOf<UMainHUDCpp> HUDClass;

};
