// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Interface/CharacterHUDInterface.h"
#include "Interface/CharacterSkillInterface.h"
#include "SoulLikeCharacter.generated.h"

UCLASS(config=Game)
class ASoulLikeCharacter : public ACharacter, 
	public ICharacterHUDInterface,
	public ICharacterSkillInterface
{
	GENERATED_BODY()
public:
	ASoulLikeCharacter();
	
protected:
	//Basic Game Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;
protected: 
	//Character Stat Section
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCharacterStatManager> StatManager;

	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UMainHUDCpp> HUDClass;

	FName CharacterName;
protected:
	//HUD Interface override Function
	virtual void InitStatUI();
protected:
	//Input Section Value Section

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> EssentialAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> EscapeAction; 
protected: //for animation blueprint
	UPROPERTY()
	FVector LastUpdatedDirection; 

	UPROPERTY()
	bool IsAttacking;
protected:
	//Essential Game Function Section
	virtual void BeginPlay();
	virtual void Tick(float delta) override;
protected: 
	//Input function Section
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void EssentialAttack(const FInputActionValue& Value); 
	virtual void Escape(const FInputActionValue& Value);
	virtual void SetUpEssentialHUD(class UMainHUDCpp* WidgetPtr) override;

	UFUNCTION(BlueprintCallable, Category = "VectorOperations")
	FVector CalculateCrossProduct() const; //for animation blueprint

	UFUNCTION(BlueprintCallable, Category = "VectorOperations")
	float CalculateDotProduct() const; //for animation blueprint not effective

	UFUNCTION()
	virtual void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted); 

	//This Method Make Statmanager to Load Charater's Essential Stat Data from Data Table
	virtual void LoadCharacterData(FName InName);
protected:
	//Skill Interface Function Override
	virtual void CostHp(float InHp) override;					//Additional API for readablility
	virtual void CostMp(float InMp) override;					//Additional API for readablility
	virtual void CostStatmina(float InStamina) override;		//Additional API for readablility
	virtual void CostBullet(uint32 InCnt) override;				//Additional API for readablility
	virtual void SetupSkill(class USkill* NewSkill) override;	//Set Skill's Data And Connect Skill With StatComponent's Delegate
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

