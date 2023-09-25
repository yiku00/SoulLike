// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <Components/SphereComponent.h>
#include "GameFramework/ProjectileMovementComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projecticle.generated.h"

UCLASS()
class SOULLIKE_API AProjecticle : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* BodyFxAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* TrailFXAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* CharacterHitAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* NoHitAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* HitWorldAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* ProjectileSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* BodyFx;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* TrailFx;
protected:

private:
	ACharacter* SpawnerRef;
	
public:	
	// Sets default values for this actor's properties
	AProjecticle();

	UFUNCTION(BlueprintCallable, Category = "VectorOperations")
	void FireInDirection(const FVector& ShootDirection, ACharacter* Caller);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	UFUNCTION()
	virtual void OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
