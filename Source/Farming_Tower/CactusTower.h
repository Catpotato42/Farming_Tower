#pragma once

#include "CoreMinimal.h"
#include "TowerBase.h"
#include "CactusTower.generated.h"

UCLASS()
class FARMING_TOWER_API ACactusTower : public ATowerBase
{
    GENERATED_BODY()

public:
    ACactusTower();
    virtual void UpdateState() override;
    virtual int IsGoodPlacement() override;

protected:
    virtual void Shoot_Implementation() override;

public:
    // Projectile to spawn
    UPROPERTY(EditAnywhere, Category = "Combat")
    TSubclassOf<class AProjectileBase> ProjectileClass;

    // Speed for radial projectiles
    UPROPERTY(EditAnywhere, Category = "Combat")
    float ProjectileSpeed = 800.f;

    // Max travel distance before destroying
    UPROPERTY(EditAnywhere, Category = "Combat")
    float MaxProjectileDistance = 1000.f;

    //Projectile amount, should never be 0 or crash will happen
    UPROPERTY(EditAnywhere, Category = "Combat")
    int ProjectileAmount = 8;
};
