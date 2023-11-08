// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Interface/CharacterHUDInterface.h"
#include "SoulLikeCharacter.generated.h"

UCLASS(config=Game)
class ASoulLikeCharacter : public ACharacter, public ICharacterHUDInterface
{
	GENERATED_BODY()
public:
	ASoulLikeCharacter(); // 
	
protected:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;
protected: //Character Stat Section
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCharacterStatManager> StatManager;

	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UMainHUDCpp> HUDClass;

	FName CharacterName;
protected:
	virtual void InitStatUI();

public:
	const float GetMaxHp();
	const float GetMaxMp();
	const float GetMaxStamina();
private: //Input Section
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;

	/*This is for Essential Attack Action that can be called very rappidly*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> EssentialAttackAction; // skill essential attack

	/*EscapeAction, player can dodge Enemy's Attack for Playing Doge Action Skill*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> EscapeAction; //not valueable more+
protected: //for animation blueprint
	UPROPERTY()
	FVector LastUpdatedDirection; 

	UPROPERTY()
	bool IsAttacking;
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay();
	virtual void Tick(float delta) override;

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
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

