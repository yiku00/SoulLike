// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GunFighterHUD.h"
#include "RevanantHUDCpp.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKE_API URevanantHUDCpp : public UGunFighterHUD
{
	GENERATED_BODY()
	
	//Function Section
public:

protected:
	virtual void NativeConstruct() override;
	virtual void BeginDestroy()override;
	virtual void NativeTick(const FGeometry& MyGeometry, float dt) override;

private:




	//Variable Section
public:

protected:

private:


	
};
