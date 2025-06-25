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

int ACactusTower::IsGoodPlacement()
{
    //Same as indicator
    int riverDist = TowerPlacement->GetRiverDistance(GetActorLocation());
    int dir = 0;
    if (riverDist < 2) //decrease level if wet
        dir = -1;
    else if (riverDist > 3 && TowerLevel < 5) //increase level if dry
        dir = 1;
    return dir;
}


void ACactusTower::UpdateState()
{
    // Compute level change based on resources
    int dir = IsGoodPlacement();
    int riverDist = TowerPlacement->GetRiverDistance(GetActorLocation());
    GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Green, FString::Printf(TEXT("River distance: %d"), riverDist));

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
                ProjectileAmount = 6;
                break;
            case 2:
                ProjectileAmount = 6;
                break;
            case 3:
                ProjectileAmount = 10;
                break;
            case 4:
                ProjectileAmount = 10;
                break;
            case 5:
                ProjectileAmount = 16;
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