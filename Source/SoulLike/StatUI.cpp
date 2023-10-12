// Fill out your copyright notice in the Description page of Project Settings.


#include "StatUI.h"
#include "CharacterStatManager.h"
#include "SoulLikeCharacter.h"

float UStatUI::GetOwningHp()
{
	if (OwnerStatData) {
		return OwnerStatData->GetCurrentHp() / OwnerStatData->GetMaxHp();
	}
	return 0.0f;
}

float UStatUI::GetOwningStamina()
{
	if (OwnerStatData) {
		return OwnerStatData->GetCurrentStamina() / OwnerStatData->GetMaxStamina();
	}
	return 0.0f;
}

void UStatUI::NativeConstruct()
{
	Super::NativeConstruct();
	OwnerStatData = OwningPawn->GetStatManager()->GetStatData();
}

void UStatUI::BeginDestroy()
{
	Super::BeginDestroy();
}

void UStatUI::NativeTick(const FGeometry& MyGeometry, float dt)
{
	Super::NativeTick(MyGeometry, dt);
}
