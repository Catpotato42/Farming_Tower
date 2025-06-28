#include "MortarTower.h"

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
                TowerDamage = 10.f;
                ProjectileSize = 1.5f;
                break;
            case 2:
                TowerDamage = 15.f;
                ProjectileSize = 1.5f;
                break;
            case 3:
                TowerDamage = 15.f;
                ProjectileSize = 1.5f;
                break;
            case 4:
                TowerDamage = 15.f;
                ProjectileSize = 2.0f;
                break;
            case 5:
                TowerDamage = 25.f;
                ProjectileSize = 2.0f;
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


void AMortarTower::Shoot_Implementation()
{

}