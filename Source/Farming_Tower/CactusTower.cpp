#include "CactusTower.h"
#include "TowerRange.h"
#include "ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ACactusTower::ACactusTower()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ACactusTower::Shoot_Implementation()
{
    if (!ProjectileClass) return;

    FVector SpawnLocation = GetActorLocation();
    FRotator Rotation;

    // Fire in 8 directions (every 45 degrees)
    for (int i = 0; i < 8; ++i)
    {
        float AngleDegrees = i * 45.0f;
        float Radians = FMath::DegreesToRadians(AngleDegrees);

        const float ProjectileRange = TowerRangeComponent->DetectionRange;
        FVector Direction = FVector(FMath::Cos(Radians), FMath::Sin(Radians), 0.f);
        FRotator SpawnRotation = Direction.Rotation();

        FActorSpawnParameters SpawnParams;
        AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(
            ProjectileClass,
            SpawnLocation,
            SpawnRotation,
            SpawnParams
        );

        if (Projectile)
        {
            Projectile->MovementComponent->Velocity = Direction * ProjectileSpeed;
            Projectile->SetLifeSpan(MaxProjectileDistance / ProjectileSpeed); // time = distance / speed
            Projectile->Range = ProjectileRange;
        }
    }
}
