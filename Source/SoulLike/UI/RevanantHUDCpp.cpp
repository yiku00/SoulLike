// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RevanantHUDCpp.h"
#include "Interface/GunFighterInterface.h"
#include "BulletWidget.h"

void URevanantHUDCpp::NativeConstruct()
{
	Super::NativeConstruct();

	//BulletUI = Cast<UBulletWidget>(GetWidgetFromName(TEXT("RevanantBulletUI")));
	//ensure(BulletUI != nullptr);

	////if Owner Pawn Has GunFighterInterface, Request Gunfight Data to Display
	//IGunFighterInterface* Interface = Cast<IGunFighterInterface>(GetOwningPlayer());
	//if (Interface)
	//{
	//	Interface->SetUpGunFightHUD(this);
	//}

}

void URevanantHUDCpp::BeginDestroy()
{
	Super::BeginDestroy();

}

void URevanantHUDCpp::NativeTick(const FGeometry& MyGeometry, float dt)
{
	Super::NativeTick(MyGeometry, dt);

}
