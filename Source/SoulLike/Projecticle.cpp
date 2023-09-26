// Fill out your copyright notice in the Description page of Project Settings.


#include "Projecticle.h"
#include "Particles/ParticleSystemComponent.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/Character.h"


// Sets default values
AProjecticle::AProjecticle()
{
    // Set this actor to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;

    // Create and configure a projectile sphere component
    ProjectileSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileSphere"));
    RootComponent = ProjectileSphere;
    ProjectileSphere->InitSphereRadius(5.0f);
    ProjectileSphere->SetCollisionProfileName(TEXT("MainProjecticle"));

    // Create a projectile movement component
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->SetUpdatedComponent(ProjectileSphere);
    ProjectileMovement->InitialSpeed = 30000.0f;
    ProjectileMovement->MaxSpeed = 30000.0f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = false;
    ProjectileMovement->Bounciness = 0.f; // Adjust if needed

    ProjectileMovement->ProjectileGravityScale = 0.f;

    BodyFx = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BodyFx"));
    BodyFx->SetupAttachment(GetRootComponent());
    BodyFx->bAutoActivate = false; 

    TrailFx = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailFx"));
    TrailFx->SetupAttachment(BodyFx);
    TrailFx->bAutoActivate = false;
    
    InitialLifeSpan = 0.2f;
    ProjectileSphere->SetSimulatePhysics(false);
    ProjectileSphere->SetNotifyRigidBodyCollision(true);
    ProjectileSphere->OnComponentHit.AddDynamic(this, &AProjecticle::OnBulletHit);

}

void AProjecticle::FireInDirection(const FVector& ShootDirection, ACharacter* Caller)
{
    SpawnerRef = Caller;
    ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
    TrailFx->SetActive(true);
    BodyFx->SetActive(true);
}

// Called when the game starts or when spawned
void AProjecticle::BeginPlay()
{
	Super::BeginPlay();
    if(BodyFxAsset)
        BodyFx->SetTemplate(BodyFxAsset);
    if(TrailFXAsset)
        TrailFx->SetTemplate(TrailFXAsset);
  
}

void AProjecticle::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    if (EndPlayReason == EEndPlayReason::Destroyed) {
        if (NoHitAsset) {
            UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), NoHitAsset, GetActorLocation(), GetActorRotation());
        }
    }
}

void AProjecticle::OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    UParticleSystem* SelectedEffect = nullptr;
    if (OtherActor == SpawnerRef)
        return;
    UE_LOG(LogTemp, Warning, TEXT("OnBulletHit"));
    if (OtherActor && (OtherActor->IsA(APawn::StaticClass()) || OtherActor->IsA(ACharacter::StaticClass())))
    {
        SelectedEffect = CharacterHitAsset;
        UE_LOG(LogTemp, Warning, TEXT("CharacterHitAsset"));
    }
    else if (OtherComp && OtherComp->IsA(UStaticMeshComponent::StaticClass()))
    {
        SelectedEffect = HitWorldAsset;
        UE_LOG(LogTemp, Warning, TEXT("HitWorldAsset"));
    }
    else {
        SelectedEffect = NoHitAsset;
        UE_LOG(LogTemp, Warning, TEXT("NoHitAsset"));
    }
    FRotator NewRotation = Hit.Normal.Rotation();
    NewRotation.Yaw -= 0;  // Yaw를 기준으로 180도 회전
    if (SelectedEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SelectedEffect, Hit.Location, NewRotation);
    }

    // 총알 액터 삭제
    Destroy();
}

// Called every frame
void AProjecticle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

