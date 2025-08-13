#include "DaisyIndicator.h"

int ADaisyIndicator::IsGoodPlacement()
{
    int riverDist = TowerPlacement->GetRiverDistance(GetActorLocation());

    int total = 0;
    if (riverDist < 2 || riverDist > 3)
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