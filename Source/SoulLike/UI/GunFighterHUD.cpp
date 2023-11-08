// Fill out your copyright notice in the Description page of Project Settings.


#include "GunFighterHUD.h"
#include "Interface/GunFighterInterface.h"
#include "BulletWidget.h"

void UGunFighterHUD::UpdateCurrentBulletCnt(const uint32 NewCnt)
{
	if (BulletUI != nullptr)
	{
		BulletUI->UpdateCurrentBullet(NewCnt);
	}
}

void UGunFighterHUD::UpdateMaxBulletCnt(const uint32 NewCnt)
{
	if (BulletUI)
	{
		BulletUI->UpdateMaxBullet(NewCnt);
	}
}

void UGunFighterHUD::NativeConstruct()
{
	Super::NativeConstruct();

	BulletUI = Cast<UBulletWidget>(GetWidgetFromName(TEXT("RevanantBulletUI")));
	ensure(BulletUI != nullptr);

	//if Owner Pawn Has GunFighterInterface, Request Gunfight Data to Display
	IGunFighterInterface* Interface = Cast<IGunFighterInterface>(GetOwningPlayerPawn());
	if (Interface)
	{
		Interface->SetUpGunFightHUD(this);
	}
}

void UGunFighterHUD::BeginDestroy()
{
	Super::BeginDestroy();
}

void UGunFighterHUD::NativeTick(const FGeometry& MyGeometry, float dt)
{
	Super::NativeTick(MyGeometry, dt);
}
