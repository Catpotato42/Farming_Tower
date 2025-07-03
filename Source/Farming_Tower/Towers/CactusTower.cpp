#include "CactusTower.h"
#include "../TowerRange.h"
#include "../Projectiles/ProjectileBase.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ACactusTower::ACactusTower()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ACactusTower::Shoot_Implementation()
{
    if (!ProjectileClass) return;

    FVector SpawnLocation = GetActorLocation() + FVector(0, 0, SpawnHeightOffset);
    FRotator Rotation;

    // Fire in *amount* directions
    for (int i = 0; i <= ProjectileAmount; ++i)
    {
        float Radians = i * (2 * PI / ProjectileAmount);

        const float ProjectileRange = TowerRangeComponent->DetectionRange + 50.0f; //How far the projectiles go
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
            Projectile->Range = ProjectileRange;
            Projectile->Damage = TowerDamage;
        }
    }
}

int ACactusTower::IsGoodPlacement()
{
    //Same as indicator
    int riverDist = TowerPlacement->GetRiverDistance(GetActorLocation());
    if (riverDist < 3) //decrease level if wet
        return -1;
    else if (riverDist > 4) //increase level if dry
        return 1;
    return 0;
}


void ACactusTower::UpdateState()
{
    Super::UpdateState();
    if (TowerLevel >= 15)
    {
        ProjectileAmount = 16;
        TowerDamage = 20.f;
        ShootInterval = 0.75f;
    }
    else if (TowerLevel >= 11)
    {
        ProjectileAmount = 12;
        TowerDamage = 15.f;
        ShootInterval = 1.0f;
    }
    else if (TowerLevel >= 7)
    {
        ProjectileAmount = 8;
        TowerDamage = 15.f;
        ShootInterval = 1.0f;
    }
    else if (TowerLevel >= 4)
    {
        ProjectileAmount = 8;
        TowerDamage = 10.f;
        ShootInterval = 1.5f;
    }
    else
    {
        ProjectileAmount = 5;
        TowerDamage = 10.f;
        ShootInterval = 1.5f;
    }
}