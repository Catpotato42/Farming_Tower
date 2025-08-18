#include "CattailIndicator.h"


int ACattailIndicator::IsGoodPlacement()
{
    int riverDist = TowerPlacement->GetRiverDistance(GetActorLocation());
    if (riverDist > 0) //decrease level if not in water
        return -1;
    else
    {
        return 1;
        //float zPos = GetActorLocation().Z;
        //return zPos <= 550 ? 1 : 0; //better if lower
    }
}