// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/RevanantBasicAttack.h"
#include "Interface/RevanantSkillInterface.h"
#include <Prop/Projecticle.h>
#include "Skill/SkillData.h"
#include <Kismet/GameplayStatics.h>

URevanantBasicAttack::URevanantBasicAttack()
{
	//Get Skill Data
	static ConstructorHelpers::FObjectFinder<USkillData> SkillDataObjRef(TEXT("/Script/SoulLike.SkillData'/Game/Skill/Revanant/DA_Revanant_BasicAttackData.DA_Revanant_BasicAttackData'"));
	if (SkillDataObjRef.Succeeded())
	{
		SkillData = SkillDataObjRef.Object;
	}

	//Get Empty Sound Asset when play there is not Current bullet
	static ConstructorHelpers::FObjectFinder<USoundBase>SoundRef(TEXT("/Script/Engine.SoundWave'/Game/Sound/SFX/Revolver/Revolver_Trigger_Pull_Empty.Revolver_Trigger_Pull_Empty'"));
	if (SoundRef.Succeeded())
	{
		EmptyBulletSound = SoundRef.Object;
	}

	//Projecticle Class to Spawn 
	static ConstructorHelpers::FClassFinder<AProjecticle> ProjecticleClassRef(TEXT("/Script/Engine.Blueprint'/Game/Characters/ParagonRevenant/Characters/RevenantProjecticle.RevenantProjecticle_C'"));
	if (ProjecticleClassRef.Succeeded())
	{
		ProjecticleClass = ProjecticleClassRef.Class;
	}
}

void URevanantBasicAttack::Execute()
{

	if (Owner != nullptr)
	{
		IRevanantSkillInterface* Revanant = Cast<IRevanantSkillInterface>(Owner);
		if (!Revanant)
		{
			return;
		}

		if (OwnersCurrentStamina >= SkillData->CostStamina && OwnersCurrentBullet >= SkillData->CostBullet && !Revanant->GetAttackFlag())
		{
			//there is Enough Bullet ,Stamina And Character is not Attacking
			Revanant->SetIsAttack(true);

			//Play Montage if Not null
			if (SkillData->ToPlayMontage != nullptr) 
			{
				Revanant->PlayMontageFromSkill(SkillData->ToPlayMontage);
			}

			if (ProjecticleClass)
			{
				AProjecticle* FiredObj =
					Revanant->GetPawnWorld()->SpawnActor<AProjecticle>(ProjecticleClass,
						Revanant->GetSocketLocation() + Revanant->GetPlayerAimingDirection() * 15.f,
						Revanant->GetPawnRotation());

				FiredObj->FireInDirection(
					GetProjecticleDirection(FiredObj->ProjectileMovement->InitialSpeed * FiredObj->GetLifeSpan()),
					Owner);
			}

			CostStat();
		}
		else if (OwnersCurrentStamina < SkillData->CostStamina)
		{
			//There is no Stamina

		}
		else if(OwnersCurrentBullet < SkillData->CostBullet){
			//PlaySound Effects Empty
			if (EmptyBulletSound) {
				UGameplayStatics::PlaySoundAtLocation(Revanant->GetPawnWorld(), EmptyBulletSound, Revanant->GetSocketLocation());
			}
		}
	}
}

bool URevanantBasicAttack::CanExecute()
{
	if (Owner != nullptr)
	{
		IRevanantSkillInterface* Revanant = Cast<IRevanantSkillInterface>(Owner);
		//Revanant Is Aiming And Not Reloading
		bool bIsExecutable = Revanant->GetAimFlag() && !Revanant->GetReloadingFlag(); 
		return bIsExecutable;
	}
	else {
		return false;
	}

}

void URevanantBasicAttack::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	ensure(SkillData != nullptr);
	ensure(Owner != nullptr);

	if (Montage == SkillData->ToPlayMontage)
	{
		IRevanantSkillInterface* Revanant = Cast<IRevanantSkillInterface>(Owner);
		if (Revanant)
		{
			Revanant->SetIsAttack(false);
		}

	}
}

FVector URevanantBasicAttack::GetProjecticleDirection(float RayDistance)
{
	if (Owner != nullptr)
	{
		IRevanantSkillInterface* Revanant = Cast<IRevanantSkillInterface>(Owner);

		FHitResult HitResult;
		FVector StartLocation = Revanant->GetCameraLocation();
		FVector EndLocation = StartLocation + (Revanant->GetPlayerAimingDirection() * RayDistance);

		FCollisionQueryParams QueryParams;
		//Make Ignore Revanant 
		QueryParams.AddIgnoredActor(Cast<AActor>(Owner));

		// Execute Ray Casting
		bool bHit = Revanant->GetPawnWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams);

		if (bHit)
		{
			// if hit some mesh, ShootDirection is 
			FVector ShootDirection = (HitResult.ImpactPoint - Revanant->GetSocketLocation()).GetSafeNormal();
			return ShootDirection;
		}
		else {
			return (EndLocation - Revanant->GetSocketLocation()).GetSafeNormal();
		}
	}
	else {
		return FVector();
	}
}
