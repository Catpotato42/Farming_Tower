#include "ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/PrimitiveComponent.h"
#include "EnemyBase.h"
#include "Engine/Engine.h"
#include "Logging/LogMacros.h"

AProjectileBase::AProjectileBase()
{
    PrimaryActorTick.bCanEverTick = true;

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    MovementComponent->InitialSpeed = 1000.f;
    MovementComponent->MaxSpeed = 1000.f;
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
    UE_LOG(LogTemp, Warning, TEXT("Projectile hit: %s"), *OtherActor->GetName());
    if (OtherActor && OtherActor->Tags.Contains("Enemy"))
    {
        AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
        if (Enemy)
        {
            Enemy->ApplyDamage(Damage);
        }
    }

    Destroy();
}