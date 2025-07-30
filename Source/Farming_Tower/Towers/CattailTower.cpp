#include "Towers/CattailTower.h"
#include "Projectiles/BeamProjectile.h"
#include "Enemies/EnemyBase.h"
#include "TowerRange.h"
#include "Kismet/GameplayStatics.h"

void ACattailTower::Tick(float DeltaTime)
{
    // (Base Tick will call Shoot if ready)
    Super::Tick(DeltaTime);

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
    // Don't shoot if already firing a beam
    if (ActiveBeam) return;

    // Get highest health enemy in range
    if (!TowerRangeComponent) return;
    TArray<AActor*> SortedEnemies = TowerRangeComponent->GetSortedEnemiesInRangeByHealth();
    if (SortedEnemies.Num() == 0) return;

    CurrentTarget = Cast<AEnemyBase>(SortedEnemies[0]);
    if (!CurrentTarget) return;

    // Spawn the beam projectile
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    FVector StartLocation = GetActorLocation();
    ABeamProjectile* Beam = GetWorld()->SpawnActor<ABeamProjectile>(
        BeamProjectileClass,
        StartLocation,
        FRotator::ZeroRotator,
        SpawnParams
    );

    if (Beam)
    {
        ActiveBeam = Beam;
        // Pass references and data to the beam
        Beam->InitBeam(this, CurrentTarget, TowerDamage, TowerRangeComponent->GetRange());

        // Bind a delegate or use an event so the beam can notify the tower when it is done
        Beam->OnBeamFinished.AddUObject(this, &ACattailTower::OnBeamFinished);
    }
}

void ACattailTower::OnBeamFinished()
{
    ActiveBeam = nullptr;
    CurrentTarget = nullptr;
    // Now the base class cooldown will allow the next shot after ShootInterval
}