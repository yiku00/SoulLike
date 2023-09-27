// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Projecticle.h"
#include "SoulLikeCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReloadNotifyDelegateForMainUI);
UCLASS(config=Game)
class ASoulLikeCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* EscapeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ReloadAction;

	UPROPERTY()
	FVector LastUpdatedDirection;

	UPROPERTY()
	int CurrentBulletCnt;

	UPROPERTY()
	int MaxBulletCnt;

	UPROPERTY()
	bool isReloading;

	UPROPERTY()
	bool IsAttacking;

	float CurrentHp;
	float MaxHp;
	float CurrentStamina;
	float MaxStamina;
	float StaminaRecoveryRate;
	float FireStaminaCost;
	float AimStaminaCost;
	float EscapeStaminaBonus;
	FVector AimingCameraLocation = FVector(290,70,90);
	FRotator AimingCameraRotation = FRotator(0, 0, 0);

	FVector NormalCameraLocation = FVector(0,0,0);
	FRotator NormalCameraRotation = FRotator(0,0,0);
public:
	ASoulLikeCharacter();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsAiming;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* FireAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* ReloadAnimMontageLong;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* ReloadAnimMontageMiddle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* ReloadAnimMontageShort;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* DodgeAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* EmptyBulletSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AProjecticle> ProjecticleClass;

	UPROPERTY(BlueprintAssignable)
	FOnReloadNotifyDelegateForMainUI OnReloadNotify;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UMainHUDCpp> BlueprintWidgetClass;
private:
	void CheckCameraLoc(float dt);
	void TickStaminaLogic(float dt);
	void TickHpLogic(float dt);
	FVector GetProjecticleDirection(float RayDistance);
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void BeginPlay();
	virtual void Tick(float delta) override;
	UFUNCTION()
	virtual void OnAnimationNotify(FName NotifyName, const FBranchingPointNotifyPayload& Payload);

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Fire(const FInputActionValue& Value);
	void Reload(const FInputActionValue& Value);
	void Escape(const FInputActionValue& Value);
	void Aim(const FInputActionValue& Value);
	void AimOff(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "VectorOperations")
	FVector CalculateCrossProduct() const;

	UFUNCTION(BlueprintCallable, Category = "VectorOperations")
	float CalculateDotProduct() const;

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	float GetCurrentHp() { return CurrentHp; } 
	float GetCurrentStamina() { return CurrentStamina; }
	float GetMaxHp() { return MaxHp; }
	float GetMaxStamina() { return MaxStamina; }

	UFUNCTION(BlueprintCallable)
	int GetCurrentBullet() { return CurrentBulletCnt; }
	UFUNCTION(BlueprintCallable)
	int GetMaxBullet() { return MaxBulletCnt; }
};

