#include "ProjectileBeam.h"
#include "../Towers/CattailTower.h"
#include "../Enemies/EnemyBase.h"
#include "Components/BoxComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

AProjectileBeam::AProjectileBeam()
{
    PrimaryActorTick.bCanEverTick = true;
    BeamMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BeamMesh"));
    RootComponent = BeamMesh;
}

void AProjectileBeam::InitBeam(ACattailTower* InTower, AEnemyBase* InTarget, float InDamagePerSecond, float InRange, float SpawnHeightOffset)
{
    UE_LOG(LogTemp, Warning, TEXT("Beam Spawned"));
    SourceTower = InTower;
    TargetEnemy = InTarget;
    MaxDamagePerSecond = InDamagePerSecond;
    UE_LOG(LogTemp, Warning, TEXT("Beam Damage: %f"), MaxDamagePerSecond);
    CurrDamagePerSecond = 1.f;
    MaxRange = InRange;
    HeightOffset = SpawnHeightOffset;
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
        UE_LOG(LogTemp, Warning, TEXT("Bye Beam"));
        Destroy();
        return;
    }

    // Check range
    float Distance = FVector::Dist(GetActorLocation(), TargetEnemy->GetActorLocation());
    if (Distance > MaxRange)
    {
        if (OnBeamFinished.IsBound())
            OnBeamFinished.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Bye Beam"));
        Destroy();
        return;
    }
    //Change DPS based on time alive
    CurrDamagePerSecond = FMath::Clamp(CurrDamagePerSecond + (MaxDamagePerSecond/2.5f)*DeltaTime, 0.f, MaxDamagePerSecond);
    UE_LOG(LogTemp, Warning, TEXT("Curr Damage: %f"), CurrDamagePerSecond);
    // Update particle timer
    ParticleTimer -= DeltaTime;


    // Apply damage using DeltaTime for consistency
    TargetEnemy->ApplyDamage(CurrDamagePerSecond * DeltaTime);
    DamageDone += CurrDamagePerSecond * DeltaTime;

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
    Direction.Normalize();
    FVector MidPoint = Start + 0.6f * Direction;
    BeamMesh->SetWorldLocation(MidPoint + FVector(0.f, 0.f, HeightOffset));

    // Set the beam's rotation to face the target plus 90 degrees along the z-axis
    FRotator BeamRotation = Direction.Rotation() + FRotator(0.f, -90.f, 90.f);
    BeamMesh->SetWorldRotation(BeamRotation);

    FVector BeamScale = BeamMesh->GetComponentScale();
    BeamScale.Z = Length / 100.f; // assuming cylinder height is 100 units
    BeamMesh->SetWorldScale3D(BeamScale);

    if (OnHitEffect && ParticleTimer <= 0.f)
        {
            ParticleTimer = 0.1f; // Reset timer
            UNiagaraFunctionLibrary::SpawnSystemAtLocation(
                GetWorld(),
                OnHitEffect,
                End,
                GetActorRotation()
            );
        }
}

void AProjectileBeam::CheckLifetime(float DeltaTime)
{
    //nothing
}

void AProjectileBeam::OnProjectileHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    //nothing
}