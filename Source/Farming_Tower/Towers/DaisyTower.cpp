#include "DaisyTower.h"
#include "TowerBase.h"
#include "../TowerRange.h"
#include "../Projectiles/ProjectileBase.h"
#include "../Projectiles/ProjectileHoming.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"

ADaisyTower::ADaisyTower()
{
    
}

void ADaisyTower::Shoot_Implementation()
{
    if (!ProjectileClass || !TowerRangeComponent) return;
    
    TArray<AActor*> EnemyList = TowerRangeComponent->GetSortedEnemiesInRange(CurrentMode);
    FVector StartLocation = GetActorLocation() + FVector(0, 0, SpawnHeightOffset);
    FCollisionQueryParams TraceParams(FName(TEXT("DaisyTrace")), true, this);
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
            UE_LOG(LogTemp, Warning, TEXT("Shoot Interval: %f"), ShootInterval);

            FActorSpawnParameters SpawnParams;

            AProjectileHoming* HomingProjectile = GetWorld()->SpawnActor<AProjectileHoming>(
                ProjectileClass,
                StartLocation,
                FRotator::ZeroRotator,
                SpawnParams
            );

            DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Yellow, false, .3f, 0, 2.f);

            if (HomingProjectile)
            {
                HomingProjectile->ProjectileSpeed = ProjectileSpeed;
                HomingProjectile->SetHomingTarget(Enemy);
                HomingProjectile->Range = MaxProjectileDistance;
                HomingProjectile->Damage = TowerDamage;
            }

            GetWorldTimerManager().SetTimer(
                SecondShotTimerHandle,
                FTimerDelegate::CreateUObject(this, &ADaisyTower::ShootSecondShot, Enemy),
                0.25f,
                false
            );

            break;
        }
    }
}

void ADaisyTower::ShootSecondShot(AActor* Enemy)
{
    if (!ProjectileClass || !Enemy) return;

    FVector StartLocation = GetActorLocation() + FVector(0, 0, SpawnHeightOffset);
    FVector EndLocation = Enemy->GetActorLocation() + FVector(0, 0, AimHeightOffset);

    FActorSpawnParameters SpawnParams;
    auto* HomingProjectile = GetWorld()->SpawnActor<AProjectileHoming>(
        ProjectileClass,
        StartLocation,
        FRotator::ZeroRotator,
        SpawnParams
    );

    DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Yellow, false, .3f, 0, 2.f);

    if (HomingProjectile)
    {
        HomingProjectile->ProjectileSpeed = ProjectileSpeed;
        HomingProjectile->SetHomingTarget(Enemy);
        HomingProjectile->Range = MaxProjectileDistance;
        HomingProjectile->Damage = TowerDamage;
    }
}


int ADaisyTower::IsGoodPlacement()
{
    int total = 0;

    int riverDist = TowerPlacement->GetRiverDistance(GetActorLocation());
    if (riverDist < 2 || riverDist > 3) //bad if immediately next to river or too far
        total--;
    
    float zPos = GetActorLocation().Z;
    if (zPos >= 700)
        total--;
    else if (zPos <= 500)
        total--;
    else
        total++;

    if (total < 0)
        return -1;
    return total;
}



void ADaisyTower::UpdateState()
{
    Super::UpdateState();
    if (TowerLevel >= 15)
    {
        TowerDamage = 10.f;
        ShootInterval = .5f;
    }
    else if (TowerLevel >= 11)
    {
        TowerDamage = 7.f;
        ShootInterval = 1.f;
    }
    else if (TowerLevel >= 7)
    {
        TowerDamage = 5.f;
        ShootInterval = 1.5f;
    }
    else if (TowerLevel >= 4)
    {
        TowerDamage = 5.f;
        ShootInterval = 2.f;
    }
    else
    {
        TowerDamage = 3.f;
        ShootInterval = 2.f;
    }
}
