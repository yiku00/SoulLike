// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SoulLikeCharacter.generated.h"

//TODO
//애니메이션 , 파티클 레퍼런스 최적화
//Animnotify혹은 AnimNotifyState 클래스 구상
//팩토리 패턴을 쓰든 뭘 하든

UCLASS(config=Game)
class ASoulLikeCharacter : public ACharacter
{
	GENERATED_BODY()

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
	class UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* EscapeAction;

	UPROPERTY()
	FVector LastUpdatedDirection;


protected:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY()
	bool IsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCharacterStatManager* StatManager;

	FName CharacterName;
public:
	ASoulLikeCharacter();

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
	TSubclassOf<class AProjecticle> ProjecticleClass;

	UPROPERTY(EditDefaultsOnly, Category = "Fx")
	class UNiagaraSystem* EscapeParticle;
private:

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void CheckCameraLoc(float dt);
	virtual void BeginPlay();
	virtual void Tick(float delta) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void Attack(const FInputActionValue& Value);
	void Escape(const FInputActionValue& Value);


	UFUNCTION(BlueprintCallable, Category = "VectorOperations")
	FVector CalculateCrossProduct() const;

	UFUNCTION(BlueprintCallable, Category = "VectorOperations")
	float CalculateDotProduct() const;

	UFUNCTION()
	virtual void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION()
	class UCharacterStatManager* GetStatManager() { return StatManager; };
};

