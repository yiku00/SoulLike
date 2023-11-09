// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UStatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SOULLIKE_API IStatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetHp(float NewHp) = 0;
	virtual void SetMp(float NewMp) = 0;
	virtual void SetStamina(float NewStamina) = 0;
	virtual void SetCurrentBullet(uint32 NewCnt) = 0;
};
