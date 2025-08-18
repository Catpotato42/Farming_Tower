#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ProjectileBeam.generated.h"

class ACattailTower;
class AEnemyBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBeamFinished);

UCLASS()
class FARMING_TOWER_API AProjectileBeam : public AProjectileBase
{
    GENERATED_BODY()

public:
    AProjectileBeam();

    virtual void Tick(float DeltaTime) override;

    // Call this to initialize the beam after spawning
    void InitBeam(ACattailTower* InTower, AEnemyBase* InTarget, float InDamagePerSecond, float InRange, float SpawnHeightOffset);

    // Delegate to notify tower when beam is finished
    UPROPERTY(BlueprintAssignable)
    FOnBeamFinished OnBeamFinished;

protected:
    UPROPERTY()
    ACattailTower* SourceTower = nullptr;

    UPROPERTY()
    AEnemyBase* TargetEnemy = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* BeamMesh = nullptr;

    float MaxDamagePerSecond = 0.f;
    float CurrDamagePerSecond = 0.f;
    float MaxRange = 0.f;
    float HeightOffset = 0.f;
    float ParticleTimer = 0.1f; // Timer for particle effects
    float DamageDone = 0.f;

    // Optionally: Visuals
    void UpdateBeamVisual();

    // Helper
    bool IsTargetValid() const;

    virtual void CheckLifetime(float DeltaTime) override;

    virtual void OnProjectileHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
};