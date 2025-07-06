#include "ProjectileMortar.h"
#include "GameFramework/ProjectileMovementComponent.h"

void AProjectileMortar::LaunchTowardsTarget(const FVector& Start, const FVector& Target, float ArcHeight)
{
    FVector Direction = Target - Start;
    float GravityAmount = FMath::Abs(GetWorld()->GetGravityZ());

    FVector FlatDir = FVector(Direction.X, Direction.Y, 0);
    float Distance = FlatDir.Size();

    float HeightDifference = Direction.Z;
    float InitialZ = FMath::Sqrt(2 * GravityAmount * ArcHeight);

    float Time = (InitialZ + FMath::Sqrt(FMath::Max(0.f, InitialZ * InitialZ + 2 * GravityAmount * (HeightDifference - ArcHeight)))) / GravityAmount;

    FVector HorizontalVel = FlatDir / Time;

    FVector InitialVelocity = HorizontalVel + FVector(0, 0, InitialZ);
    MovementComponent->Velocity = InitialVelocity;
}
