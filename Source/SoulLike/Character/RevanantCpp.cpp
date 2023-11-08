// Fill out your copyright notice in the Description page of Project Settings.


#include "RevanantCpp.h"
#include "CharacterStat/CharacterStatManager.h"
#include <EnhancedInputComponent.h>
#include <Kismet/GameplayStatics.h>
#include "Prop/Projecticle.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "UI/GunFighterHUD.h"
#include "Player/SoulLikePlayerController.h"

ARevanantCpp::ARevanantCpp()
{
	AimStaminaCost = 15.f;
	FireStaminaCost = 30.f;
	EscapeStaminaBonus = 50.f;

	AimingCameraTransform = FTransform(
		FRotator(0, 0, 0),
		FVector(290, 70, 90),
		FVector(1, 1, 1));

	NormalCameraTransform = FTransform(
		FRotator(0, 0, 0),
		FVector(0, 0, 0),
		FVector(1, 1, 1));

	//Set Character's name
	CharacterName = FName(TEXT("Revanant"));
	LoadCharacterData(CharacterName);

	//Get Revanant's HUD CLASS , need to set
	ConstructorHelpers::FClassFinder<UGunFighterHUD> StatWidgetClassRef(TEXT("/Game/UI/BPRevanantStatUI.BPRevanantStatUI_C"));
	if (StatWidgetClassRef.Succeeded())
	{
		HUDClass = StatWidgetClassRef.Class;
	}
}

void ARevanantCpp::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Super::OnMontageEnded(Montage, bInterrupted);

	//if (Montage == MontageData.EssentialAttackMontage[0])
	//{
	//	//IsAttacking = false;
	//}
	//else if (Montage == MontageData.ReloadAnimMontage[0])
	//{
	//	//isReloading = false;
	//	//CurrentBulletCnt = MaxBulletCnt;
	//}
	//else if (Montage == MontageData.SkillMontage1[0]) {
	//	//UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f); // 원래 속도로 시간이 흐른다
	//	//CustomTimeDilation = 1.0f; // 플레이어도 원래 속도로 움직인다
	//	//GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed / 2;
	//	//StaminaRecoveryRate -= EscapeStaminaBonus;
	//	//NSComponent->Deactivate();
	//}
}

void ARevanantCpp::BeginPlay()
{
	Super::BeginPlay();
	//Send Request to Controller to set HUD Class, so when game begin, HUD Class Will be Constructed

	ASoulLikePlayerController* PlayerController = Cast<ASoulLikePlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->SetHUDClass(HUDClass);
	}
}

void ARevanantCpp::Aim(const FInputActionValue& Value)
{
	Super::Aim(Value);
	//StatManager->EditStaminaRoveryRate(-AimStaminaCost);
	IsAiming = true;
	bUseControllerRotationYaw = true;
}

void ARevanantCpp::AimOff(const FInputActionValue& Value)
{
	//StatManager->EditStaminaRoveryRate(AimStaminaCost);
	IsAiming = false;
	bUseControllerRotationYaw = false;
}

void ARevanantCpp::Reload(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Reload"));
	//if (CurrentBulletCnt == MaxBulletCnt)return;
	//isReloading = true;
	//if (MontageData.ReloadAnimMontage.Num() != 0) {
	//	PlayAnimMontage(MontageData.ReloadAnimMontage[0]);
	//	OnReloadNotify.Broadcast();
	//}
}

void ARevanantCpp::Attack(const FInputActionValue& Value)
{
	//if (isReloading || !IsAiming)return;
	//if (CurrentBulletCnt > 0 && StatManager->GetStatData()->CurrentStamina > FireStaminaCost)
	//{

	//	IsAttacking = true;

	//	if (MontageData.EssentialAttackMontage.Num() != 0) {
	//		PlayAnimMontage(MontageData.EssentialAttackMontage[0]);
	//	}

	//	CurrentBulletCnt--;
	//	StatManager->CostStamina(FireStaminaCost);

	//	AProjecticle* FiredObj =
	//		GetWorld()->SpawnActor<AProjecticle>(ProjecticleClass,
	//			GetMesh()->GetSocketLocation(FName(TEXT("FX_GUN_MUZZLE"))) + FollowCamera->GetForwardVector() * 15.f,
	//			GetActorRotation());


	//	FiredObj->FireInDirection(
	//		GetProjecticleDirection(FiredObj->ProjectileMovement->InitialSpeed * FiredObj->GetLifeSpan()),
	//		this);
	//}
	//else if (StatManager->GetStatData()->CurrentStamina < FireStaminaCost)
	//{
	//	//There is no Stamina

	//}
	//else {
	//	//PlaySound Effects Empty
	//	if (EmptyBulletSound) {
	//		UGameplayStatics::PlaySoundAtLocation(this, EmptyBulletSound, GetActorLocation());
	//	}
	//}
}

void ARevanantCpp::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &ARevanantCpp::Aim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &ARevanantCpp::AimOff);

		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &ARevanantCpp::Reload);
	}
}

void ARevanantCpp::Tick(float delta)
{
	Super::Tick(delta);

}

void ARevanantCpp::CheckCameraLoc(float dt)
{
	Super::CheckCameraLoc(dt);
}

FVector ARevanantCpp::GetProjecticleDirection(float RayDistance)
{
	return Super::GetProjecticleDirection(RayDistance);
}


