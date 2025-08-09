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
    void InitBeam(ACattailTower* InTower, AEnemyBase* InTarget, float InDamagePerSecond, float InRange);

    // Delegate to notify tower when beam is finished
    UPROPERTY(BlueprintAssignable)
    FOnBeamFinished OnBeamFinished;

protected:
    UPROPERTY()
    ACattailTower* SourceTower = nullptr;

    UPROPERTY()
    AEnemyBase* TargetEnemy = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Beam")
    UStaticMeshComponent* BeamMesh = nullptr;

    float DamagePerSecond = 0.f;
    float MaxRange = 0.f;

    // Optionally: Visuals
    void UpdateBeamVisual();

    // Helper
    bool IsTargetValid() const;

    
};