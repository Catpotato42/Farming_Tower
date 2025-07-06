#include "ProjectileHoming.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectileHoming::AProjectileHoming()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AProjectileHoming::SetHomingTarget(AActor* Target)
{
    if (Target)
    {
        MovementComponent->bIsHomingProjectile = false; // no built in homing
        HomingTarget = Target->GetRootComponent();
    }
}

void AProjectileHoming::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!IsValid(HomingTarget) || !IsValid(MovementComponent))
    {
        Destroy();
        return;
    }

    FVector Direction = (HomingTarget->GetComponentLocation() - GetActorLocation()).GetSafeNormal();
    MovementComponent->Velocity = Direction * ProjectileSpeed;
}