// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainHUDCpp.h"
#include "GunFighterHUD.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKE_API UGunFighterHUD : public UMainHUDCpp
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	TObjectPtr<class UBulletWidget> BulletUI;
public:
	UFUNCTION()
	virtual void UpdateCurrentBulletCnt(const uint32 NewCnt);
	virtual void UpdateMaxBulletCnt(const uint32 NewCnt);
protected:
	virtual void NativeConstruct();
	virtual void BeginDestroy();
	virtual void NativeTick(const FGeometry& MyGeometry, float dt);

private:

};
