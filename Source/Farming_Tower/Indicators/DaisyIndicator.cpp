#include "DaisyIndicator.h"

int ADaisyIndicator::IsGoodPlacement()
{
    int riverDist = TowerPlacement->GetRiverDistance(GetActorLocation());

    int total = 0;
    if (riverDist < 3 || riverDist > 4)
        total--;
    
    float zPos = GetActorLocation().Z;
    if (zPos >= 800)
        total--;
    else if (zPos <= 600)
        total++;

    if (total < 0)
        return -1;
    return total;
}