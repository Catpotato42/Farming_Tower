#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerBase.generated.h"

class UTowerRange;

UCLASS()
class FARMING_TOWER_API ATowerBase : public AActor
{
    GENERATED_BODY()
	
public:	
    ATowerBase();

protected:
    virtual void BeginPlay() override;

public:	
    virtual void Tick(float DeltaTime) override;

    // Called to attempt a shoot action. Override this in child classes
    UFUNCTION(BlueprintNativeEvent, Category = "Combat")
    void Shoot();
    virtual void Shoot_Implementation();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UTowerRange* TowerRangeComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float ShootInterval = 1.0f;

    //Projectile spawn height
    UPROPERTY(EditAnywhere, Category = "Combat")
    float SpawnHeightOffset = 50.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float TowerDamage = 10.f;


    float TimeSinceLastShot = 0.0f;
};
