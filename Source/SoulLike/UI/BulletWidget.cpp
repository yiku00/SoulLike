// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BulletWidget.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"

void UBulletWidget::PlayReloadAnim()
{
	if (ReloadAnim)
	{
		PlayAnimation(ReloadAnim);
	}
}

void UBulletWidget::UpdateCurrentBullet(const uint32 NewBullet)
{
	CurrentBulletAmount = NewBullet;

	CurrentBulletTextBlock->SetText(FText::FromString(FString::FromInt(CurrentBulletAmount)));
}

void UBulletWidget::UpdateMaxBullet(const uint32 NewBullet)
{
	MaxBulletAmount = NewBullet;

	CurrentBulletTextBlock->SetText(FText::FromString(FString::FromInt(MaxBulletAmount)));
}

void UBulletWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CurrentBulletTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtCurrentBullet")));
	ensure(CurrentBulletTextBlock != nullptr);

	MaxBulletTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtMaxBullet")));
	ensure(MaxBulletTextBlock != nullptr);

	ReloadAnim = Cast<UWidgetAnimation>(GetWidgetFromName(TEXT("SpinAnim")));
	ensure(ReloadAnim != nullptr);
}
