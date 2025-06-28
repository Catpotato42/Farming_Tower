// Fill out your copyright notice in the Description page of Project Settings.


#include "SniperTower.h"
#include "TowerBase.h"
#include "TowerRange.h"
#include "ProjectileBase.h"
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


int ASniperTower::IsGoodPlacement()
{
    int total = 0;

    int riverDist = TowerPlacement->GetRiverDistance(GetActorLocation());
    if (riverDist < 2 || riverDist > 5) //bad if immediately next to river or too far
        total--;
    
    float zPos = GetActorLocation().Z;
    if (zPos > 250)
        total++;
    else if (zPos < 100)
        total--;

    if (total < 0)
        return -1;
    return total;
}



void ASniperTower::UpdateState()
{
    // Compute level change based on resources
    int dir = IsGoodPlacement();
    int riverDist = TowerPlacement->GetRiverDistance(GetActorLocation());

    TowerLevel = FMath::Clamp(TowerLevel + dir, 0, 5);

    if (TowerLevel == 0)
    {
        Destroy();
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Yellow, FString::Printf(TEXT("Tower Level: %d"), TowerLevel));
        switch (TowerLevel) {
            case 1:
                TowerDamage = 10.f;
                ShootInterval = 3.0f;
                break;
            case 2:
                ProjectileAmount = 10.f;
                ShootInterval = 2.5f;
                break;
            case 3:
                ProjectileAmount = 20.f;
                ShootInterval = 2.5f;
                break;
            case 4:
                ProjectileAmount = 20.f;
                ShootInterval = 2.0f;
                break;
            case 5:
                ProjectileAmount = 30.f;
                ShootInterval = 1.5f;
                break;
            default:
            break;
        }
    }
    
    // Update UI & scale
    if (TowerUI)
    {
        UTowerUI* UIScript = Cast<UTowerUI>(TowerUI->GetUserWidgetObject());
        if (UIScript)
        {
            UIScript->UpdateLevel(TowerLevel);
        }
    }
    SetActorScale3D(FVector(0.7f + 0.1f * TowerLevel));
}