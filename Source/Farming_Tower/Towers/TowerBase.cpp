#include "TowerBase.h"
#include "../TowerRange.h"

ATowerBase::ATowerBase()
{
    PrimaryActorTick.bCanEverTick = true;

    TowerRangeComponent = CreateDefaultSubobject<UTowerRange>(TEXT("TowerRangeComponent"));

    TargetingModes = {
        ETargetingMode::ClosestToEnd,
        ETargetingMode::HighestHealth,
        ETargetingMode::LowestHealth,
        ETargetingMode::ClosestToBeginning,
        ETargetingMode::ClosestToTower
    };
    CurrentMode = TargetingModes[0];
}

void ATowerBase::BeginPlay()
{
    Super::BeginPlay();
    TimeSinceLastShot = ShootInterval - .01f;
    bDeferCooldownStart = false;
    TowerUI = FindComponentByClass<UWidgetComponent>();
}

void ATowerBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    TimeSinceLastShot += DeltaTime;

    if (TowerRangeComponent)
    {
        TowerRangeComponent->UpdateIsEnemyInRangeOnly();
        if (TowerRangeComponent->bIsEnemyInRange && TimeSinceLastShot >= ShootInterval)
        {
            
            Shoot();
            if (!bDeferCooldownStart)
            {
                TimeSinceLastShot = 0.0f;
            }
        }
    }

    if (TowerUI)
    {
        FRotator CameraRotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation();
        FRotator OppositeRotation = CameraRotation + FRotator(90.f, 180.f, 0.f);
        TowerUI->SetWorldRotation(OppositeRotation);
    }
    else
    {
        TowerUI = FindComponentByClass<UWidgetComponent>();
    }
}

void ATowerBase::Shoot_Implementation()
{
    // Intentionally empty: subclasses should override this
    UE_LOG(LogTemp, Warning, TEXT("Base tower shoot called - override this."));
}

void ATowerBase::UpdateState()
{
    // Compute level change based on resources
    int dir = IsGoodPlacement();
    int riverDist = TowerPlacement->GetRiverDistance(GetActorLocation());

    TowerLevel = FMath::Clamp(TowerLevel + dir, 0, 15);
    if (TowerLevel >= 15)
        DisplayLevel = 5;
    else if (TowerLevel >= 11)
        DisplayLevel = 4;
    else if (TowerLevel >= 7)
        DisplayLevel = 3;
    else if (TowerLevel >= 4)
        DisplayLevel = 2;
    else
        DisplayLevel = 1;

    if (TowerLevel == 0)
    {
        Destroy();
    }

    // Update UI & scale
    if (TowerUI)
    {
        UTowerUI* UIScript = Cast<UTowerUI>(TowerUI->GetUserWidgetObject());
        if (UIScript)
        {
            UIScript->UpdateLevel(DisplayLevel);
        }
    }
    SetActorScale3D(FVector(0.5f + 0.05f * TowerLevel));
}

void ATowerBase::UpdateTowerUI()
{
    int dir = IsGoodPlacement();
    int riverDist = TowerPlacement->GetRiverDistance(GetActorLocation());
    if (TowerUI)
    {
        UTowerUI* UIScript = Cast<UTowerUI>(TowerUI->GetUserWidgetObject());
        if (UIScript)
        {
            int elevation = FMath::RoundToInt(GetActorLocation().Z / 100.0f) * 10 - 20;
            bool lvlUp = ((dir == 1) && (TowerLevel == 14 || TowerLevel == 10 || TowerLevel == 6 || TowerLevel == 3)) || ((dir == -1) && (TowerLevel == 15 || TowerLevel == 11 || TowerLevel == 7 || TowerLevel == 4 || TowerLevel == 1));
            UIScript->UpdateUI(dir, riverDist, lvlUp, elevation);
        }
    }
}

void ATowerBase::NextTargetMode()
{
    CurrentModeIndex = (CurrentModeIndex + 1) % TargetingModes.Num();
    CurrentMode = TargetingModes[CurrentModeIndex];
}

void ATowerBase::PreviousTargetMode()
{
    CurrentModeIndex = (CurrentModeIndex - 1 + TargetingModes.Num()) % TargetingModes.Num();
    CurrentMode = TargetingModes[CurrentModeIndex];
}