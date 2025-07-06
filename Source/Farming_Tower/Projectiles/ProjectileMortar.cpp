#include "ProjectileMortar.h"
#include "GameFramework/ProjectileMovementComponent.h"

void AProjectileMortar::LaunchTowardsTarget(const FVector& Start, const FVector& Target, float ArcHeight)
{
    if (!MovementComponent) return;

    FVector Direction = Target - Start;
    FVector FlatDirection = FVector(Direction.X, Direction.Y, 0.f);
    float Distance = FlatDirection.Size();

    float GravityZ = FMath::Abs(GetWorld()->GetGravityZ());
    float HeightOffset = Direction.Z;

    if (GravityZ <= 0.f || Distance <= 0.f) return;

    // Initial Z velocity to reach arc height
    float InitialZ = FMath::Sqrt(2.f * GravityZ * ArcHeight);

    // Total time = time to reach peak + time from peak to target height
    float TimeUp = InitialZ / GravityZ;
    float TimeDown = FMath::Sqrt(FMath::Max(0.f, 2.f * (ArcHeight - HeightOffset) / GravityZ));
    float TotalTime = TimeUp + TimeDown;

    if (TotalTime <= 0.f) return;

    FVector HorizontalVelocity = FlatDirection / TotalTime;
    FVector FinalVelocity = HorizontalVelocity + FVector(0, 0, InitialZ);
    FinalVelocity = FinalVelocity.GetClampedToMaxSize(1800.f);

    MovementComponent->Velocity = FinalVelocity;
    MovementComponent->ProjectileGravityScale = 1.0f;
}