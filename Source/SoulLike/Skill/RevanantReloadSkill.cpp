// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/RevanantReloadSkill.h"
#include <Interface/RevanantSkillInterface.h>
#include "Skill/SkillData.h"

URevanantReloadSkill::URevanantReloadSkill()
{
	//Get Skill Data
	static ConstructorHelpers::FObjectFinder<USkillData> SkillDataObjRef(TEXT("/Script/SoulLike.SkillData'/Game/Skill/Revanant/DA_Revanant_Reload.DA_Revanant_Reload'"));
	if (SkillDataObjRef.Succeeded())
	{
		SkillData = SkillDataObjRef.Object;
	}
}

void URevanantReloadSkill::Execute()
{
	ensure(SkillData != nullptr);
	ensure(Owner != nullptr);

	if (!SkillData || !Owner)
	{
		return;
	}

	IRevanantSkillInterface* Revanant = Cast<IRevanantSkillInterface>(Owner);
	if (Revanant)
	{
		if (!Revanant->GetReloadingFlag() && 
			!Revanant->GetAttackFlag() && 
			OwnersCurrentBullet < OwnersMaxBullet)
		{
			//Character Is Not Reloading, And Is Not Attacking, And Need To Fill Some Bullet
			Revanant->SetIsReloading(true);
			Revanant->PlayMontageFromSkill(SkillData->ToPlayMontage);
		}
	}
}

void URevanantReloadSkill::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (!SkillData || !Owner)
	{
		return;
	}

	if (Montage == SkillData->ToPlayMontage)
	{
		IRevanantSkillInterface* Revanant = Cast<IRevanantSkillInterface>(Owner);
		Revanant->FillBulletMax();
		Revanant->SetIsReloading(false);
	}
}
