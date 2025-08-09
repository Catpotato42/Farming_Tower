#include "TowerPlacement.h"

int ATowerPlacement::GetRiverDistance(FVector loc)
{
    if (CheckRiverDistance(loc, 0.3f))
    {
        return 0;
    }
    for (int i = 1; i < 10; i++)
    {
        if (CheckRiverDistance(loc, i))
        {
            return i;
        }
    }
    return 10;
}

bool ATowerPlacement::CheckRiverDistance(FVector loc, int distance)
{
    if (distance == 0)
    {
        FHitResult DownHit;
        FVector Start = loc + FVector(0, 0, 50);
        FVector End = loc - FVector(0, 0, 10000);

        FCollisionQueryParams Params;
        Params.AddIgnoredActor(this);

        while (GetWorld()->LineTraceSingleByChannel(DownHit, Start, End, ECC_Visibility, Params))
        {
            AActor* HitActor = DownHit.GetActor();
            if (!HitActor)
                break;

            if (HitActor->ActorHasTag("River"))
                return true;

            if (!HitActor->ActorHasTag("Tower"))
                break;

            Params.AddIgnoredActor(HitActor);
            Start = DownHit.ImpactPoint - FVector(0, 0, 1);
        }

        return false;
    }

    // Sphere check for distance > 0
    TArray<FHitResult> HitResults;
    FCollisionShape Sphere = FCollisionShape::MakeSphere(distance * 100);

    bool bHit = GetWorld()->SweepMultiByChannel(
        HitResults,
        loc,
        loc,
        FQuat::Identity,
        ECC_Pawn,
        Sphere
    );

    for (const FHitResult& Hit : HitResults)
    {
        if (Hit.GetActor() && Hit.GetActor()->ActorHasTag("River"))
            return true;
    }

    return false;
}