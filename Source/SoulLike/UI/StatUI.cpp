// Fill out your copyright notice in the Description page of Project Settings.


#include "StatUI.h"
#include "CharacterStat/CharacterStatManager.h"
#include "Character/SoulLikeCharacter.h"
#include "Components/ProgressBar.h"
#include <Components/CanvasPanelSlot.h>

void UStatUI::UpdateHpPercentage(const float NewHp)
{
	float NewPercentage = FMath::Clamp(NewHp,0, OwnersMaxHp) / OwnersMaxHp;
	HPProgressBar->SetPercent(NewPercentage);
}

void UStatUI::UpdateMpPercentage(const float NewMp)
{
	float NewPercentage = FMath::Clamp(NewMp, 0, OwnersMaxMp) / OwnersMaxMp;
	MPProgressBar->SetPercent(NewPercentage);
}

void UStatUI::UpdateStaminaPercentage(const float NewStamina)
{
	float NewPercentage = FMath::Clamp(NewStamina, 0, OwnersMaxStamina) / OwnersMaxStamina;
	StaminaProgressBar->SetPercent(NewPercentage);
}

void UStatUI::SetMaxHp(const float NewHp)
{
	OwnersMaxHp = NewHp;

	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(HPProgressBar->Slot);
	FVector2D NewSize = FVector2D(NewHp*3, CanvasSlot->GetSize().Y);

	if (CanvasSlot)
	{
		CanvasSlot->SetSize(NewSize);
	}
}

void UStatUI::SetMaxMp(const float NewMp)
{
	OwnersMaxMp = NewMp;
	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(MPProgressBar->Slot);
	FVector2D NewSize = FVector2D(NewMp*3, CanvasSlot->GetSize().Y);

	if (CanvasSlot)
	{
		CanvasSlot->SetSize(NewSize);
	}
}

void UStatUI::SetMaxStamina(const float NewStamina)
{
	OwnersMaxStamina = NewStamina;
	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(StaminaProgressBar->Slot);
	FVector2D NewSize = FVector2D(NewStamina*3, CanvasSlot->GetSize().Y);

	if (CanvasSlot)
	{
		CanvasSlot->SetSize(NewSize);
	}
}

void UStatUI::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPPB")));
	ensure(HPProgressBar != nullptr);

	MPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MPPB")));
	ensure(MPProgressBar != nullptr);

	StaminaProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("StaminaPB")));
	ensure(StaminaProgressBar != nullptr);
	//OwnerStatData = OwningPawn->GetStatManager()->GetStatData();
}

void UStatUI::BeginDestroy()
{
	Super::BeginDestroy();
}

void UStatUI::NativeTick(const FGeometry& MyGeometry, float dt)
{
	Super::NativeTick(MyGeometry, dt);
}
