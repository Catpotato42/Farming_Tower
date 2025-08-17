#pragma once

#include "CoreMinimal.h"

#include "../TowerPlacement.h"
#include "../UI/TowerUI.h"

#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"

#include "GameFramework/Actor.h"
#include "TowerBase.generated.h"


class UTowerRange;

UENUM(BlueprintType)
enum class ETargetingMode : uint8
{
    ClosestToEnd        UMETA(DisplayName = "Closest to End"),
    HighestHealth       UMETA(DisplayName = "Highest Health"),
    LowestHealth        UMETA(DisplayName = "Lowest Health"),
    ClosestToBeginning  UMETA(DisplayName = "Closest to Beginning"),
    ClosestToTower      UMETA(DisplayName = "Closest to Tower")
};

UCLASS()
class FARMING_TOWER_API ATowerBase : public AActor
{
    GENERATED_BODY()
	
public:	
    ATowerBase();

    virtual void Tick(float DeltaTime) override;

    // Called to attempt a shoot action. Override this in child classes
    UFUNCTION(BlueprintNativeEvent, Category = "Combat")
    void Shoot();
    virtual void Shoot_Implementation();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Targeting")
    bool SupportsTargetingModes() const;
    virtual bool SupportsTargetingModes_Implementation() const { return true; }

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targeting")
    ETargetingMode CurrentMode = ETargetingMode::ClosestToEnd;

    virtual int IsGoodPlacement() { return 0;}
    virtual void UpdateState();
    UFUNCTION(BlueprintCallable)
    virtual void UpdateTowerUI();
    virtual void ChangeDisplayLevel();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower Placement")
    ATowerPlacement* TowerPlacement;

    UFUNCTION(BlueprintCallable, Category = "Targeting")
    void NextTargetMode();

    UFUNCTION(BlueprintCallable, Category = "Targeting")
    void PreviousTargetMode();

protected:
    virtual void BeginPlay() override;

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
    int RoundsLived = 1;
    bool dying = false;

    bool bDeferCooldownStart = false;

    float TimeSinceLastShot = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Targeting")
    TArray<ETargetingMode> TargetingModes;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targeting")
    int32 CurrentModeIndex = 0;
};
