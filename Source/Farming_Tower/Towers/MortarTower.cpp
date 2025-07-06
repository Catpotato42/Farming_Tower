#include "MortarTower.h"
#include "../TowerRange.h"
#include "../Enemies/EnemyBase.h"
#include "Components/SplineComponent.h"
#include "../Projectiles/ProjectileBase.h"
#include "../Projectiles/ProjectileMortar.h"

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
    if (TowerLevel >= 15)
    {
        TowerDamage = 25.f;
        ProjectileSize = 2.0f;
    }
    else if (TowerLevel >= 11)
    { 
        TowerDamage = 15.f;
        ProjectileSize = 2.0f;
    }
    else if (TowerLevel >= 7)
    {
        TowerDamage = 15.f;
        ProjectileSize = 1.5f;
    }
    else if (TowerLevel >= 4)
    {
        TowerDamage = 15.f;
        ProjectileSize = 1.5f;
    }
    else
    {
        TowerDamage = 10.f;
        ProjectileSize = 1.5f;
    }
}


void AMortarTower::Shoot_Implementation()
{
    if (!ProjectileClass || !TowerRangeComponent) return;

    TArray<AActor*> EnemyList = TowerRangeComponent->GetSortedEnemiesInRangeByEndProgress();
    FVector StartLocation = GetActorLocation() + FVector(0, 0, SpawnHeightOffset);

    for (AActor* Actor : EnemyList)
    {
        AEnemyBase* Enemy = Cast<AEnemyBase>(Actor);
        if (!Enemy || !Enemy->PathSpline) continue;

        float Speed = Enemy->Speed;
        float CurrentDist = Enemy->DistanceTraveled;

        float PredictTime = 1.0f;
        float FutureDistance = CurrentDist + Speed * PredictTime;

        FVector PredictedLocation = Enemy->PathSpline->GetLocationAtDistanceAlongSpline(FutureDistance, ESplineCoordinateSpace::World);

        FActorSpawnParameters SpawnParams;
        AProjectileMortar* Projectile = GetWorld()->SpawnActor<AProjectileMortar>(
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
            Projectile->LaunchTowardsTarget(StartLocation, PredictedLocation, 2000.f); // Change arc height
        }

        break;
    }
}