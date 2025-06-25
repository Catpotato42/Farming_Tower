// Fill out your copyright notice in the Description page of Project Settings.


#include "SniperTower.h"

void ASniperTower::ShootImplementation()
{
    if (!ProjectileClass) return;

    TArray<AActor*> EnemyList = TowerRangeComponent->GetSortedEnemiesInRangeByEndProgress();
    FVector StartLocation = GetActorLocation() + FVector(0, 0, SpawnHeightOffset);
    FCollisionQueryParams TraceParams(FName(TEXT("SniperTrace")), true, this);
    TraceParams.AddIgnoredActor(this);

    for (AActor* Enemy : EnemyList)
    {
        if (!Enemy) continue;

        FHitResult HitResult;
        FVector EndLocation = Enemy->GetActorLocation();

        bool bHit = GetWorld()->LineTraceSingleByChannel(
            HitResult,
            StartLocation,
            EndLocation,
            ECC_Visibility,
            TraceParams
        );

        if (bHit && HitResult.GetActor() == Enemy)
        {
            FRotator FireRotation = (EndLocation - StartLocation).Rotation();
            FActorSpawnParameters SpawnParams;

            AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(
                ProjectileClass,
                StartLocation,
                FireRotation,
                SpawnParams
            );

            if (Projectile)
            {
                Projectile->MovementComponent->Velocity = FireRotation.Vector() * ProjectileSpeed;
                Projectile->Range = MaxProjectileDistance;
                Projectile->Damage = TowerDamage;
            }
            break;
        }
    }
}

