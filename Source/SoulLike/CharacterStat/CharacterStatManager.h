// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStat/CharacterDataStructures.h"
#include "Interface/StatInterface.h"
#include "CharacterStatManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpUpdated,float)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMpUpdated, float)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStaminaUpdated, float)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCurrentBulletChanged, uint32)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOULLIKE_API UCharacterStatManager : public UActorComponent
{
	GENERATED_BODY()
public:	
	//Essential Character Stat Function Section
	UCharacterStatManager();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void LoadCharacterData(FName CharacterName);
	void LoadGunFighterCharacterData(FName CharacterName);
	FORCEINLINE const float GetMaxHp() { return CharacterData.MaxHp; }
	FORCEINLINE const float GetMaxMp() { return CharacterData.MaxMp; }
	FORCEINLINE const float GetMaxStamina() { return CharacterData.MaxStamina; }
	FORCEINLINE const float GetCurrentHp() { return CurrentHp; }
	FORCEINLINE const float GetCurrentMp() { return CurrentMp; }
	FORCEINLINE const float GetCurrentStamina() { return CurrentStamina; }
	FORCEINLINE const uint32 GetMaxBullet() { return GunFighterData.MaxBulletCnt; }
	FORCEINLINE const float GetCurrentBullet() { return CurrentBulletCnt; }

	//Essential Character Stat Function Section
	void SetCurrentHp(const float NewHp);
	void SetCurrentMp(const float NewMp);
	void SetCurrentStamina(const float NewStamina);
	void SetCurrentBullet(const uint32 NewCnt);

	//Additional API 
	void CostHp(const float InHp);
	void CostMp(const float InMp);
	void CostStamina(const float InStamina);
	void CostBullet(const uint32 InCnt);
protected:
	// Essential virtual Function
	virtual void BeginPlay() override;
	void TickStaminaLogic(float dt);
	void TickHpLogic(float dt);
private:
	

public:
	//these delegate should be connected in Character's class
	FOnHpUpdated OnHpUpdatedDelegate;
	FOnMpUpdated OnMpUpdatedDelegate;
	FOnStaminaUpdated OnStaminaUpdatedDelegate;
	FOnCurrentBulletChanged OnCurrentBulletUpdated;
private:
	UPROPERTY()
	FCharacterData CharacterData;

	UPROPERTY()
	FGunFighterData GunFighterData; //if Character is not Gunfighter, THis Value will be null

	UPROPERTY()
	float CurrentHp;

	UPROPERTY()
	float CurrentMp;

	UPROPERTY()
	float CurrentStamina;

	UPROPERTY()
	uint32 CurrentBulletCnt;
};
