// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStatManager.h"
#include <Subsystems/PanelExtensionSubsystem.h>
#include "MainHUDCpp.h"

// Sets default values for this component's properties
UCharacterStatManager::UCharacterStatManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	CharacterData = nullptr;
}


// Called when the game starts
void UCharacterStatManager::BeginPlay()
{
	Super::BeginPlay();
}

void UCharacterStatManager::TickStaminaLogic(float dt)
{
	if (!CharacterData)return;
	if (CharacterData->CurrentStamina >= CharacterData->MaxStamina) {
		CharacterData->CurrentStamina = CharacterData->MaxStamina;
		return;
	}

	CharacterData->CurrentStamina += CharacterData->StaminaRecoveryRate * dt;
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

void UCharacterStatManager::LoadCharacterData(FName* CharacterName)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerDataTableAsset(TEXT("/Script/Engine.DataTable'/Game/DataTable/StatData.StatData'"));
	if (PlayerDataTableAsset.Succeeded())
	{
		UDataTable* PlayerDataTable = PlayerDataTableAsset.Object;

		CharacterData = PlayerDataTable->FindRow<FCharacterData>(*CharacterName, FString());
		if (CharacterData) {
			InitStatUI();
			UE_LOG(LogTemp, Display, TEXT("CharacterData Load Success"));
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

void UCharacterStatManager::CostStamina(float val)
{
	CharacterData->CurrentStamina -= val;
	if (CharacterData->CurrentStamina < 0)CharacterData->CurrentStamina = 0;
}

void UCharacterStatManager::EditStaminaRoveryRate(float val)
{
	CharacterData->StaminaRecoveryRate += val;
}

void UCharacterStatManager::InitStatUI()
{
	if (APawn* OwnerPawn = Cast<APawn>(GetOwner()))
	{
		APlayerController* OwnerController = Cast<APlayerController>(OwnerPawn->GetController());
		if (OwnerController && BlueprintWidgetClass)
		{
			UUserWidget* MyWidget = CreateWidget<UUserWidget>(OwnerController, BlueprintWidgetClass);
			if (MyWidget)
			{
				MyWidget->AddToViewport(); // 위젯을 뷰포트에 추가합니다.
			}
		}
	}
}

