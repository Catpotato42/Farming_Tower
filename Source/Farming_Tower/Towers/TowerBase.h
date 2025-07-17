#pragma once

#include "CoreMinimal.h"

#include "../TowerPlacement.h"
#include "../UI/TowerUI.h"

#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"

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

    virtual int IsGoodPlacement() { return 0;}
    virtual void UpdateState();
    UFUNCTION(BlueprintCallable)
    virtual void UpdateTowerUI();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower Placement")
    ATowerPlacement* TowerPlacement;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UTowerRange* TowerRangeComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
    class UWidgetComponent* TowerUI;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float ShootInterval = .3f;

    //Projectile spawn height
    UPROPERTY(EditAnywhere, Category = "Combat")
    float SpawnHeightOffset = 50.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float TowerDamage = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    int TowerLevel = 1;
    int DisplayLevel = 1;

    float TimeSinceLastShot = 0.0f;
};
