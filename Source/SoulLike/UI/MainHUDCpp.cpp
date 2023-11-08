// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUDCpp.h"
#include "Character/CharacterStatManager.h"
#include "Character/SoulLikeCharacter.h"
#include "Components/ProgressBar.h"
#include <Components/CanvasPanelSlot.h>
#include "BulletWidget.h"

void UMainHUDCpp::UpdateHpPercentage(const float NewHp)
{
	float NewPercentage = FMath::Clamp(NewHp, 0, OwnersMaxHp) / OwnersMaxHp;
	HPProgressBar->SetPercent(NewPercentage);
}

void UMainHUDCpp::UpdateMpPercentage(const float NewMp)
{
	float NewPercentage = FMath::Clamp(NewMp, 0, OwnersMaxMp) / OwnersMaxMp;
	MPProgressBar->SetPercent(NewPercentage);
}

void UMainHUDCpp::UpdateStaminaPercentage(const float NewStamina)
{
	float NewPercentage = FMath::Clamp(NewStamina, 0, OwnersMaxStamina) / OwnersMaxStamina;
	StaminaProgressBar->SetPercent(NewPercentage);
}

void UMainHUDCpp::SetMaxHp(const float NewHp)
{
	OwnersMaxHp = NewHp;

	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(HPProgressBar->Slot);
	FVector2D NewSize = FVector2D(NewHp * 3, CanvasSlot->GetSize().Y);

	if (CanvasSlot)
	{
		CanvasSlot->SetSize(NewSize);
	}
}

void UMainHUDCpp::SetMaxMp(const float NewMp)
{
	OwnersMaxMp = NewMp;
	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(MPProgressBar->Slot);
	FVector2D NewSize = FVector2D(NewMp * 3, CanvasSlot->GetSize().Y);

	if (CanvasSlot)
	{
		CanvasSlot->SetSize(NewSize);
	}
}

void UMainHUDCpp::SetMaxStamina(const float NewStamina)
{
	OwnersMaxStamina = NewStamina;
	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(StaminaProgressBar->Slot);
	FVector2D NewSize = FVector2D(NewStamina * 3, CanvasSlot->GetSize().Y);

	if (CanvasSlot)
	{
		CanvasSlot->SetSize(NewSize);
	}
}

void UMainHUDCpp::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPPB")));
	ensure(HPProgressBar != nullptr);

	MPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MPPB")));
	ensure(MPProgressBar != nullptr);

	StaminaProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("StaminaPB")));
	ensure(StaminaProgressBar != nullptr);
	
	BulletUI = Cast<UBulletWidget>(GetWidgetFromName(TEXT("RevanantBulletUI")));
	ensure(BulletUI != nullptr);
}

void UMainHUDCpp::BeginDestroy()
{
	Super::BeginDestroy();
}

void UMainHUDCpp::NativeTick(const FGeometry& MyGeometry, float dt)
{
	Super::NativeTick(MyGeometry, dt);
}