#include "ProjectileBeam.h"
#include "../Towers/CattailTower.h"
#include "../Enemies/EnemyBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AProjectileBeam::AProjectileBeam()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AProjectileBeam::InitBeam(ACattailTower* InTower, AEnemyBase* InTarget, float InDamagePerSecond, float InRange)
{
    SourceTower = InTower;
    TargetEnemy = InTarget;
    DamagePerSecond = InDamagePerSecond;
    MaxRange = InRange;
    SetActorTickEnabled(true);
    // Optionally: Initialize visuals here
}

void AProjectileBeam::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!IsTargetValid())
    {
        if (OnBeamFinished.IsBound())
            OnBeamFinished.Broadcast();
        Destroy();
        return;
    }

    // Check range
    float Distance = FVector::Dist(GetActorLocation(), TargetEnemy->GetActorLocation());
    if (Distance > MaxRange)
    {
        if (OnBeamFinished.IsBound())
            OnBeamFinished.Broadcast();
        Destroy();
        return;
    }

    // Apply damage using DeltaTime for consistency
    TargetEnemy->ApplyDamage(DamagePerSecond * DeltaTime);

    // Update beam position/visuals
    UpdateBeamVisual();
}

bool AProjectileBeam::IsTargetValid() const
{
    return TargetEnemy && !TargetEnemy->IsPendingKillPending() && TargetEnemy->GetHealth() > 0.f;
}

void AProjectileBeam::UpdateBeamVisual()
{
    if (!BeamMesh || !SourceTower || !TargetEnemy) return;

    FVector Start = SourceTower->GetActorLocation();
    FVector End = TargetEnemy->GetActorLocation();
    FVector Direction = End - Start;
    float Length = Direction.Size();

    // Set the beam's position to the midpoint
    FVector MidPoint = Start + 0.5f * Direction;
    BeamMesh->SetWorldLocation(MidPoint);

    // Set the beam's rotation to face the target
    FRotator BeamRotation = Direction.Rotation();
    BeamMesh->SetWorldRotation(BeamRotation);

    FVector BeamScale = BeamMesh->GetComponentScale();
    BeamScale.Z = Length / 100.f; // assuming cylinder height is 100 units
    BeamMesh->SetWorldScale3D(BeamScale);
}