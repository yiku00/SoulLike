// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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
	//InitHUD(const TSubclassOf<class MainHUDCpp> HUDClass);
protected:
	virtual void BeginPlay() override;
private:

};
