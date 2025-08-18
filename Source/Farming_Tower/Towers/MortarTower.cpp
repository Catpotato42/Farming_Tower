#include "MortarTower.h"
#include "../TowerRange.h"
#include "../Enemies/EnemyBase.h"
#include "Components/SplineComponent.h"
#include "../Projectiles/ProjectileBase.h"
#include "../Projectiles/ProjectileMortar.h"
#include "../Projectiles/ProjectileMortarExploding.h"

AMortarTower::AMortarTower()
{
    
}

int AMortarTower::IsGoodPlacement()
{
    int total = 0;

    int riverDist = TowerPlacement->GetRiverDistance(GetActorLocation());
    if (riverDist > 4)
        total--;
    else if (riverDist < 3)
        total++;

    //check sunlight

    if (total < 0)
        return -1;
    else if (total > 0)
        return 1;
    return 0;
}


void AMortarTower::UpdateState()
{
    Super::UpdateState();
    if (TowerLevel >= 8)
    { 
        TowerDamage = 35.f;
        ProjectileSize = 3.f;
        ShootInterval = 2.f;
        ExplosionRadius = 250.f;
    }
    else if (TowerLevel >= 6)
    {
        TowerDamage = 25.f;
        ProjectileSize = 2.f;
        ShootInterval = 3.f;
        ExplosionRadius = 215.f;
    }
    else if (TowerLevel >= 4)
    {
        TowerDamage = 20.f;
        ProjectileSize = 1.5f;
        ShootInterval = 3.5f;
        ExplosionRadius = 140.f;
    }
    else
    {
        TowerDamage = 15.f;
        ProjectileSize = 1.5f;
        ShootInterval = 3.5f;
        ExplosionRadius = 125.f; // Default
    }
}


void AMortarTower::Shoot_Implementation()
{
    if (!ProjectileClass || !TowerRangeComponent) return;

    TArray<AActor*> EnemyList = TowerRangeComponent->GetSortedEnemiesInRange(CurrentMode);
    FVector StartLocation = GetActorLocation() + FVector(0, 0, SpawnHeightOffset); // Projectile spawns above tower

    for (AActor* Actor : EnemyList) // Every actor in range (Closest enemies to end first!)
    {
        AEnemyBase* Enemy = Cast<AEnemyBase>(Actor);
        if (!Enemy || !Enemy->PathSpline) continue; // Need spline for loc

        float Speed = Enemy->Speed; // NOT current velo as a vector or something, constant speed at which the enemy travels along spline path
        float CurrentDist = Enemy->DistanceTraveled;

        float PredictTime = 1.8f; // Only independent variable, more means projectile is launched farther ahead on the path 
        float FutureDistance = CurrentDist + Speed * PredictTime;
        FVector PredictedLocation = Enemy->PathSpline->GetLocationAtDistanceAlongSpline(FutureDistance, ESplineCoordinateSpace::World);

        FActorSpawnParameters SpawnParams;
        AProjectileMortarExploding* Projectile = GetWorld()->SpawnActor<AProjectileMortarExploding>(
            ProjectileClass,
            StartLocation,
            FRotator::ZeroRotator,
            SpawnParams
        );

        if (Projectile)
        {
            Projectile->Damage = TowerDamage;
            Projectile->Range = MaxProjectileDistance;
            Projectile->Gravity = true;
            Projectile->ExplosionRadius = ExplosionRadius;
            Projectile->LaunchTowardsTarget(StartLocation, PredictedLocation, 400.f); 
            // Arc height is visual only, but too high and projectile will despawn before landing (change MaxProjectileDistance for more duration)
        }

        break;
    }
}