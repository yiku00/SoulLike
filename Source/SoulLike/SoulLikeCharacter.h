// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SoulLikeCharacter.generated.h"


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
	USoundBase* EmptyBulletSound;
private:
	void CheckCameraLoc(float dt);
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float delta) override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
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
};

