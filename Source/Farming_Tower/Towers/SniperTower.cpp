#include "SniperTower.h"
#include "TowerBase.h"
#include "../TowerRange.h"
#include "../Projectiles/ProjectileBase.h"
#include "../Projectiles/ProjectileHoming.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASniperTower::ASniperTower()
{
    
}

void ASniperTower::Shoot_Implementation()
{
    if (!ProjectileClass || !TowerRangeComponent) return;

    TArray<AActor*> EnemyList = TowerRangeComponent->GetSortedEnemiesInRangeByEndProgress();
    FVector StartLocation = GetActorLocation() + FVector(0, 0, SpawnHeightOffset);
    FCollisionQueryParams TraceParams(FName(TEXT("SniperTrace")), true, this);
    TraceParams.AddIgnoredActor(this);

    for (AActor* Enemy : EnemyList)
    {
        if (!Enemy) continue;

        FHitResult HitResult;
        FVector EndLocation = Enemy->GetActorLocation() + FVector(0, 0, AimHeightOffset);


        bool bHit = GetWorld()->LineTraceSingleByChannel(
            HitResult,
            StartLocation,
            EndLocation,
            ECC_Visibility,
            TraceParams
        );

        if (bHit && HitResult.GetActor() == Enemy)
        {
            FActorSpawnParameters SpawnParams;

            AProjectileHoming* HomingProjectile = GetWorld()->SpawnActor<AProjectileHoming>(
                ProjectileClass,
                StartLocation,
                FRotator::ZeroRotator,
                SpawnParams
            );
            DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, .5f, 0, 2.f);

            if (HomingProjectile)
            {
                HomingProjectile->ProjectileSpeed = ProjectileSpeed;
                HomingProjectile->SetHomingTarget(Enemy);
                HomingProjectile->Range = MaxProjectileDistance;
                HomingProjectile->Damage = TowerDamage;
            }
            break;
        }
    }
}


int ASniperTower::IsGoodPlacement()
{
    int total = 0;

    int riverDist = TowerPlacement->GetRiverDistance(GetActorLocation());
    if (riverDist < 2 || riverDist > 5) //bad if immediately next to river or too far
        total--;
    
    float zPos = GetActorLocation().Z;
    if (zPos >= 700)
        total++;
    else if (zPos <= 400)
        total--;

    if (total < 0)
        return -1;
    return total;
}



void ASniperTower::UpdateState()
{
    Super::UpdateState();
    if (TowerLevel >= 15)
    {
        TowerDamage = 60.f;
        ShootInterval = 1.5f;
    }
    else if (TowerLevel >= 11)
    {
        TowerDamage = 40.f;
        ShootInterval = 2.f;
    }
    else if (TowerLevel >= 7)
    {
        TowerDamage = 40.f;
        ShootInterval = 3.f;
    }
    else if (TowerLevel >= 4)
    {
        TowerDamage = 30.f;
        ShootInterval = 4.f;
    }
    else
    {
        TowerDamage = 25.f;
        ShootInterval = 5.f;
    }
}