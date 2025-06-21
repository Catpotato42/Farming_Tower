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

void ACactusTower::UpdateTowerUI()
{
    int riverDist = TowerPlacement->GetRiverDistance(GetActorLocation());
    int dir = 0;
    if (riverDist < 2) //decrease level if wet
        dir = -1;
    else if (riverDist > 5 && TowerLevel < 5) //increase level if dry
        dir = 1;

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Direction: %d"), dir));
    if (TowerUI)
    {
        UTowerUI* UIScript = Cast<UTowerUI>(TowerUI->GetUserWidgetObject());
        if (UIScript)
        {
            UIScript->UpdateUI(dir, riverDist);
        }
    }
}

void ACactusTower::UpdateState()
{
    // Compute level change based on resources
    int riverDist = TowerPlacement->GetRiverDistance(GetActorLocation());
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("River distance: %d"), riverDist));

    if (riverDist < 2) //decrease level if wet
        TowerLevel--;
    else if (riverDist > 5 && TowerLevel < 5) //increase level if dry
        TowerLevel++;

    if (TowerLevel == 0)
    {
        Destroy();
    }
    else
    {
        //change stats based on level
    }
    
    // Log the current state for debugging
    UE_LOG(LogTemp, Warning, TEXT("Cactus Tower updated: Level %d"), TowerLevel);
    if (TowerUI)
    {
        UTowerUI* UIScript = Cast<UTowerUI>(TowerUI->GetUserWidgetObject());
        if (UIScript)
        {
            UIScript->UpdateLevel(TowerLevel);
        }
    }
}