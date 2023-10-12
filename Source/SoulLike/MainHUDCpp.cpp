// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUDCpp.h"
#include "SoulLikeCharacter.h"
#include "Components/Image.h"

void UMainHUDCpp::NativeConstruct()
{
	Super::NativeConstruct();
	OwningPawn = Cast<ASoulLikeCharacter>(GetOwningPlayerPawn());
}

void UMainHUDCpp::BeginDestroy()
{
	Super::BeginDestroy();
}

void UMainHUDCpp::NativeTick(const FGeometry& MyGeometry,float dt)
{
	Super::NativeTick(MyGeometry,dt);

}