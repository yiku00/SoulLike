// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUDCpp.h"

float UMainHUDCpp::GetOwningHp()
{
	if (OwningPawn) {
		return OwningPawn->GetCurrentHp() / OwningPawn->GetMaxHp();
	}
	return 0.0f;
}

float UMainHUDCpp::GetOwningStamina()
{
	if (OwningPawn) {
		return OwningPawn->GetCurrentStamina() / OwningPawn->GetMaxStamina();
	}
	return 0.0f;
}

int UMainHUDCpp::GetCurrentBullet()
{
	if (OwningPawn) {
		return OwningPawn->GetCurrentBullet();
	}
	return 0;
}

void UMainHUDCpp::NativeConstruct()
{
	Super::NativeConstruct();
	OwningPawn = Cast<ASoulLikeCharacter>(GetOwningPlayerPawn());
	if (!OwningPawn) { UE_LOG(LogTemp, Error, TEXT("UMainHUDCpp Cast faild to Owning Pawn")); }

}
