// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SoulLikePlayerController.h"
#include "UI/MainHUDCpp.h"

void ASoulLikePlayerController::BeginPlay()
{
	// if HUDClass is valid, Create HUD And add UI to viewPort
	if (HUDClass != nullptr) 
	{
		APlayerController* OwnerController = Cast<APlayerController>(this);
		MainHUD = CreateWidget<UMainHUDCpp>(OwnerController, HUDClass.Get());
		if (MainHUD)
		{
			MainHUD->AddToViewport();
		}
	}
}
