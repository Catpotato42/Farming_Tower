#include "ProjectileBase.h"
#include "../Enemies/EnemyBase.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/ShapeComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/Engine.h"
#include "Logging/LogMacros.h"


AProjectileBase::AProjectileBase()
{
    PrimaryActorTick.bCanEverTick = true;

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    MovementComponent->bShouldBounce = false;
}

void AProjectileBase::BeginPlay()
{
    Super::BeginPlay();

    StartLocation = GetActorLocation();

    if (!Gravity) {
        MovementComponent->ProjectileGravityScale = 0.0f;
    }

    if (MyCollisionComponent)
    {
        MyCollisionComponent->OnComponentHit.AddDynamic(this, &AProjectileBase::OnProjectileHit);
        MyCollisionComponent->SetNotifyRigidBodyCollision(true);
        MyCollisionComponent->SetGenerateOverlapEvents(true);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("MyCollisionComponent is null on projectile"));
    }
}

void AProjectileBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    float DistanceTraveled = FVector::Dist(StartLocation, GetActorLocation());
    if (DistanceTraveled >= Range)
    {
        Destroy();
    }
}

void AProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor->Tags.Contains("Enemy"))
    {
        AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
        if (Enemy)
        {
            Enemy->ApplyDamage(Damage);
            UE_LOG(LogTemp, Log, TEXT("Projectile hit enemy: %s"), *OtherActor->GetName());
            UE_LOG(LogTemp, Log, TEXT("Damage applied: %f"), Damage);
            UE_LOG(LogTemp, Log, TEXT("Projectile ID: %s"), *GetName());
        }
        if (OnHitEffect)
        {
            UNiagaraFunctionLibrary::SpawnSystemAtLocation(
                GetWorld(),
                OnHitEffect,
                GetActorLocation(),
                GetActorRotation()
            );
        }
    }

    Destroy();
}