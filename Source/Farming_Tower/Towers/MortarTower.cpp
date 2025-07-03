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

}