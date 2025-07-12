#include "ProjectileMortar.h"
#include "GameFramework/ProjectileMovementComponent.h"

void AProjectileMortar::LaunchTowardsTarget(const FVector& Start, const FVector& Target, float ArcHeight)
{
    if (!MovementComponent) return;
    
    MovementComponent->ProjectileGravityScale = 1.0f;

    FVector Direction = Target - Start;
    FVector FlatDir = FVector(Direction.X, Direction.Y, 0.f);
    float Distance = FlatDir.Size(); // Doesn't return amount elements in the vector, returns magnitude of the vector

    float GravityZ = FMath::Abs(GetWorld()->GetGravityZ()); // Gravity is a negative value
    float HeightOffset = Direction.Z; // Height offset between the enemy and the projectile

    if (GravityZ <= 0.f || Distance <= 0.f) return;

    // If the enemy is higher than ArcHeight above the initial projectile spawn (which it probably isn't) this changes the arc height to the height offset + 20
    ArcHeight = FMath::Max(ArcHeight, HeightOffset + 20.f);

    // Initial Z velocity to reach arc height
    float InitialZ = FMath::Sqrt(2.f * GravityZ * ArcHeight);

    // Total time in the air, this is all vertical stuff
    float TimeUp = InitialZ / GravityZ;
    float TimeDown = FMath::Sqrt(2.f * (ArcHeight - HeightOffset) / GravityZ);
    float TotalTime = TimeUp + TimeDown;

    if (TotalTime <= 0.f) return;

    // Now add horizontal velocity
    FVector HorizontalVelocity = FlatDir / TotalTime;
    FVector FinalVelocity = HorizontalVelocity + FVector(0, 0, InitialZ);
    FinalVelocity = FinalVelocity.GetClampedToMaxSize(2200.f); // Only thing that could potentially break, but 2200 should be high enough

    MovementComponent->Velocity = FinalVelocity;
}