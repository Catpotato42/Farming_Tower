#include "CactusIndicator.h"


int ACactusIndicator::IsGoodPlacement()
{
    int riverDist = TowerPlacement->GetRiverDistance(GetActorLocation());
    if (riverDist < 2) //decrease level if wet
        return -1;
    else if (riverDist > 3) //increase level if dry
        return 1;
    return 0;
}