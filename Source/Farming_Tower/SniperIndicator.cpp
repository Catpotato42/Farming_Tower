#include "SniperIndicator.h"


int ASniperIndicator::IsGoodPlacement()
{
    int riverDist = TowerPlacement->GetRiverDistance(GetActorLocation());

    int total = 0;
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