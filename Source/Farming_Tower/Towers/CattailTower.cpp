#include "CattailTower.h"
#include "../Projectiles/ProjectileBeam.h"
#include "../Enemies/EnemyBase.h"
#include "../TowerRange.h"
#include "Kismet/GameplayStatics.h"

void ACattailTower::Tick(float DeltaTime)
{
    // (Base Tick will call Shoot if ready)
    Super::Tick(DeltaTime);
    GEngine->AddOnScreenDebugMessage(-1, .1f, FColor::Yellow, FString::Printf(TEXT("BeamCooldownTimer: %f"), BeamCooldownTimer));

    // If beam is active, do not allow base class to reset cooldown
    if (ActiveBeam)
    {
        // Optionally: update visuals or logic here
        return;
    }

    // If beam just finished, start cooldown
    if (BeamCooldownTimer > 0.f)
    {
        BeamCooldownTimer -= DeltaTime;
        if (BeamCooldownTimer <= 0.f)
        {
            BeamCooldownTimer = 0.f;
            // Allow shooting again
        }
        return;
    }
}

void ACattailTower::Shoot_Implementation()
{
    //Don't shoot if firing a beam or in cooldown
    if (ActiveBeam || BeamCooldownTimer > 0.01f) return;
    UE_LOG(LogTemp, Warning, TEXT("Starting to shoot"));

    // Get highest health enemy in range
    if (!TowerRangeComponent) return;
    TArray<AActor*> SortedEnemies = TowerRangeComponent->GetSortedEnemiesInRangeByHealth();
    UE_LOG(LogTemp, Warning, TEXT("Enemies in range: %d"), SortedEnemies.Num());
    if (SortedEnemies.Num() == 0) return;

    CurrentTarget = Cast<AEnemyBase>(SortedEnemies[0]);
    if (!CurrentTarget) return;

    // Spawn the beam projectile
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    FVector StartLocation = GetActorLocation();
    AProjectileBeam* Beam = GetWorld()->SpawnActor<AProjectileBeam>(
        BeamProjectileClass,
        StartLocation,
        FRotator::ZeroRotator,
        SpawnParams
    );
    UE_LOG(LogTemp, Warning, TEXT("Spawned Beam"));

    if (Beam)
    {
        ActiveBeam = Beam;
        // Pass references and data to the beam
        Beam->InitBeam(this, CurrentTarget, TowerDamage, TowerRangeComponent->DetectionRange);

        // Bind a delegate or use an event so the beam can notify the tower when it is done
        Beam->OnBeamFinished.AddDynamic(this, &ACattailTower::OnBeamFinished);
    }
}

void ACattailTower::OnBeamFinished()
{
    UE_LOG(LogTemp, Warning, TEXT("Beam finished"));
    ActiveBeam = nullptr;
    CurrentTarget = nullptr;
    BeamCooldownTimer = ShootInterval; // Start cooldown now
    TimeSinceLastShot = 0.f; // Prevent base class from shooting immediately
}

int ACattailTower::IsGoodPlacement()
{
    int riverDist = TowerPlacement->GetRiverDistance(GetActorLocation());
    if (riverDist > 1) //decrease level if not in water
        return -1;
    else
    {
        float zPos = GetActorLocation().Z;
        return zPos <= 550 ? 1 : 0; //better if lower
    }
}


void ACattailTower::UpdateState()
{
    Super::UpdateState();
    if (TowerLevel >= 15)
    {
        TowerDamage = 20.f;
    }
    else if (TowerLevel >= 11)
    {
        TowerDamage = 15.f;
    }
    else if (TowerLevel >= 7)
    {
        TowerDamage = 15.f;
    }
    else if (TowerLevel >= 4)
    {
        TowerDamage = 10.f;
    }
    else
    {
        TowerDamage = 10.f;
    }
}