#include "ProjectileMortarExploding.h"
#include "Kismet/GameplayStatics.h"
#include "../Enemies/EnemyBase.h"
#include "../VFX/ExplosionSphereActor.h"
#include "GameFramework/DamageType.h"
#include "Engine/EngineTypes.h"
#include "Engine/DamageEvents.h"

void AProjectileMortarExploding::OnProjectileHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    float ExplosionDamage = Damage; // Use your projectile's damage
    FVector ExplosionLocation = GetActorLocation();
    if (OtherActor && OtherActor->IsA<AEnemyBase>())
    {
        ExplosionLocation.Z -= 50.f;
    }

    TArray<AActor*> FoundEnemies;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBase::StaticClass(), FoundEnemies);

    for (AActor* Actor : FoundEnemies)
    {
        if (FVector::Dist(Actor->GetActorLocation(), ExplosionLocation) <= ExplosionRadius)
        {
            FDamageEvent DamageEvent;
            Actor->TakeDamage(ExplosionDamage, DamageEvent, GetInstigatorController(), this);
        }
    }

    // TODO: Add real explosion VFX
    // Spawn a temporary white sphere for explosion VFX
    FActorSpawnParameters VFXSpawnParams;
    AActor* ExplosionVFX = GetWorld()->SpawnActor<AActor>(
        AExplosionSphereActor::StaticClass(), // Replace with your sphere actor class
        ExplosionLocation,
        FRotator::ZeroRotator,
        VFXSpawnParams
    );

    // Optionally set material to white here if needed

    // Destroy the VFX actor after a short delay (e.g., 0.3 seconds)
    if (ExplosionVFX)
    {
        float SphereScale = ExplosionRadius / 50.f; // Default UE sphere radius is 50 units
        ExplosionVFX->SetActorScale3D(FVector(SphereScale));
        ExplosionVFX->SetLifeSpan(0.3f);
    }

    Destroy();
}