// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "CharacterStatManager.generated.h"

USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxHp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float CurrentHp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float CurrentStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float StaminaRecoveryRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float AttackStaminaCost;

	friend class UCharacterStatManager;
public:
	FCharacterData()
	{

	}

	float GetMaxHp() { return MaxHp; };
	float GetCurrentHp() { return CurrentHp; };
	float GetMaxStamina() { return MaxStamina; };
	float GetCurrentStamina() { return CurrentStamina; };
	float GetStaminaRecoveryRate() { return StaminaRecoveryRate; };
	float GetFireStaminaCost() { return AttackStaminaCost; };
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOULLIKE_API UCharacterStatManager : public UActorComponent
{
	GENERATED_BODY()
private:
	FCharacterData* CharacterData;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UMainHUDCpp> BlueprintWidgetClass;
public:	
	// Sets default values for this component's properties
	UCharacterStatManager();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void LoadCharacterData(FName* CharacterName);
	FCharacterData* GetStatData() { return CharacterData; };
	void CostStamina(float val);
	void EditStaminaRoveryRate(float val);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void TickStaminaLogic(float dt);
	void TickHpLogic(float dt);
private:
	void InitStatUI();
};
