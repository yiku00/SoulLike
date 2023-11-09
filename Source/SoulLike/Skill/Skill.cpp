// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill.h"
#include"SkillData.h"
#include "Interface/CharacterSKillInterface.h"

void USkill::Initialize(class UObject* InCharacter)
{
	if (InCharacter != nullptr)
	{
		Owner = InCharacter;

		ICharacterSkillInterface* CharacterInterface = Cast<ICharacterSkillInterface>(Owner);
		if (CharacterInterface)
		{
			CharacterInterface->SetupSkill(this);
			bIsInitialiezed = true;
		}
	}

	ensure(Owner != nullptr);
	ensure(SkillData != nullptr);
}

void USkill::SetUpAnimDelegate(FOnMontageEndedMCDelegate& Delegate)
{
	Delegate.AddDynamic(this, &USkill::OnMontageEnded);
}

USkill::USkill()
{
	bIsInitialiezed = false;
}

void USkill::Execute()
{
	
}

bool USkill::CheckHasEnoughStat()
{
	ensure(SkillData != nullptr);
	//is there enough stat to execute
	bool bIsEnoughBullet = SkillData->CostBullet <= OwnersCurrentBullet;
	bool bIsEnoughHp = SkillData->CostHp < OwnersCurrentHp;
	bool bIsEnoughMp = SkillData->CostMp < OwnersCurrentMp;
	bool bIsEnoughStamina = SkillData->CostStamina < OwnersCurrentStamina;

	return bIsEnoughBullet && bIsEnoughHp && bIsEnoughMp && bIsEnoughStamina;
}

void USkill::CostStat()
{
	ensure(SkillData != nullptr);

	ICharacterSkillInterface* CharacterInterface = Cast<ICharacterSkillInterface>(Owner);
	if (CharacterInterface)
	{
		//Cost Stat
		if (SkillData->CostBullet > 0)
		{
			CharacterInterface->CostBullet(SkillData->CostBullet);
		}
		if (SkillData->CostStamina > 0)
		{
			CharacterInterface->CostStatmina(SkillData->CostStamina);
		}
		if (SkillData->CostHp > 0)
		{
			CharacterInterface->CostHp(SkillData->CostHp);
		}
		if (SkillData->CostMp > 0)
		{
			CharacterInterface->CostMp(SkillData->CostMp);
		}
	}
}

void USkill::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{

}
