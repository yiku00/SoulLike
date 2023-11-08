// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStatManager.h"
#include <Subsystems/PanelExtensionSubsystem.h>
#include "UI/MainHUDCpp.h"

// Sets default values for this component's properties
UCharacterStatManager::UCharacterStatManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCharacterStatManager::BeginPlay()
{
	Super::BeginPlay();
}

void UCharacterStatManager::TickStaminaLogic(float dt)
{
	if (CurrentStamina >= CharacterData.MaxStamina) 
	{
		CurrentStamina = CharacterData.MaxStamina;
	}
	else 
	{
		CurrentStamina += CharacterData.StaminaRecoveryRate * dt;
	}
	SetStamina(CurrentStamina);
}

void UCharacterStatManager::TickHpLogic(float dt)
{

}


// Called every frame
void UCharacterStatManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TickStaminaLogic(DeltaTime);
	TickHpLogic(DeltaTime);
	// ...
}

void UCharacterStatManager::LoadCharacterData(FName CharacterName)
{
	UDataTable* PlayerDataTableAsset = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTable/StatData.StatData'")));
	if (PlayerDataTableAsset)
	{
		FCharacterData* RowData = PlayerDataTableAsset->FindRow<FCharacterData>(CharacterName, FString());

		if (RowData) {
			CharacterData = *RowData;
			SetHp(CharacterData.MaxHp);
			SetMp(CharacterData.MaxMp);
			SetStamina(CharacterData.MaxStamina);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("CharacterData Load Fail"));
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("UDataTable Load Fail"));
	}


}

void UCharacterStatManager::LoadGunFighterCharacterData(FName CharacterName)
{
	UDataTable* GunFighterDataTableAsset = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_GunFighterStatData.DT_GunFighterStatData'")));
	if (GunFighterDataTableAsset)
	{
		FGunFighterData* RowData = GunFighterDataTableAsset->FindRow<FGunFighterData>(CharacterName, FString());

		if (RowData) {
			GunFighterData = *RowData;
			SetCurrentBullet(GunFighterData.MaxBulletCnt);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("CharacterData Load Fail"));
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("UDataTable Load Fail"));
	}
}
