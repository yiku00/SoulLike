// Fill out your copyright notice in the Description page of Project Settings.


#include "RevanantStatUI.h"
#include "Character/RevanantCpp.h"

int URevanantStatUI::GetCurrentBullet()
{
	if (OwnedRevanant) {
		return OwnedRevanant->GetCurrentBullet();
	}
	return 0;
}

void URevanantStatUI::PlaySpinAnim()
{
	if (RevolverImage_SPin)
		PlayAnimation(RevolverImage_SPin);
}

void URevanantStatUI::NativeConstruct()
{
	Super::NativeConstruct();
	//if (!Cast<ARevanantCpp>(OwningPawn)) { UE_LOG(LogTemp, Error, TEXT("UMainHUDCpp Cast faild to Owning Pawn")); }
	//else {
	//	OwnedRevanant = Cast<ARevanantCpp>(OwningPawn);
	//	OwnedRevanant->OnReloadNotify.AddDynamic(this, &URevanantStatUI::PlaySpinAnim);
	//}
}

void URevanantStatUI::BeginDestroy()
{
	Super::BeginDestroy();
	if (OwnedRevanant)
	{
		OwnedRevanant->OnReloadNotify.RemoveDynamic(this, &URevanantStatUI::PlaySpinAnim);
	}
}

void URevanantStatUI::NativeTick(const FGeometry& MyGeometry, float dt)
{
	Super::NativeTick(MyGeometry, dt);
}
