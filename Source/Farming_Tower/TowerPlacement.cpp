#include "TowerPlacement.h"

int ATowerPlacement::GetRiverDistance(FVector loc)
{
    for (int i = 0; i < 2; i++)
    {
        if (CheckRiverDistance(loc, i+1))
        {
            return i;
        }
    }
    return 2;
}

bool ATowerPlacement::CheckRiverDistance(FVector loc, int distance)
{
    TArray<FHitResult> HitResults;

    FCollisionShape Sphere = FCollisionShape::MakeSphere(distance*100);

    // Use ECC_Pawn or another channel depending on what you're checking
    bool bHit = GetWorld()->SweepMultiByChannel(
        HitResults,
        loc,
        loc,
        FQuat::Identity,
        ECC_Pawn,
        Sphere
    );

    // Now filter by tag
    for (FHitResult hit : HitResults)
    {
        if (hit.GetActor()->ActorHasTag("River"))
        {
            return true;
        }
    }
    return false;
}