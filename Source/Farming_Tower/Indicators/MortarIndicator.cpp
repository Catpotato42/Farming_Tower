#include "MortarIndicator.h"


int AMortarIndicator::IsGoodPlacement()
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