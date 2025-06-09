#include "ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "EnemyBase.h"

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

    if (CollisionComponent)
    {
        CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectileBase::OnProjectileHit);
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
        }
    }

    Destroy();
}
