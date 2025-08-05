#include "TowerBase.h"
#include "../TowerRange.h"

ATowerBase::ATowerBase()
{
    PrimaryActorTick.bCanEverTick = true;

    TowerRangeComponent = CreateDefaultSubobject<UTowerRange>(TEXT("TowerRangeComponent"));

    if (TowerRangeComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("TowerRangeComponent initialized, owner: %s"), TowerRangeComponent->GetOwner() ? *TowerRangeComponent->GetOwner()->GetName() : TEXT("nullptr"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("TowerRangeComponent is nullptr!"));
    }
}

void ATowerBase::BeginPlay()
{
    Super::BeginPlay();
    TimeSinceLastShot = ShootInterval - .01f;
    TowerUI = FindComponentByClass<UWidgetComponent>();
}

void ATowerBase::Tick(float DeltaTime)
{
    if (HasAnyFlags(RF_ClassDefaultObject)) return;
    UE_LOG(LogTemp, Warning, TEXT("UpdateIsEnemyInRangeOnly called on: %s, IsCDO: %d"),
        GetOwner() ? *GetOwner()->GetName() : TEXT("nullptr"),
        HasAnyFlags(RF_ClassDefaultObject));
    UE_LOG(LogTemp, Warning, TEXT("Ticking: %s, IsCDO: %d"), *GetName(), HasAnyFlags(RF_ClassDefaultObject));
    Super::Tick(DeltaTime);

    TimeSinceLastShot += DeltaTime;

    if (TowerRangeComponent && TowerRangeComponent->GetOwner())
    {
        TowerRangeComponent->UpdateIsEnemyInRangeOnly();

        if (TowerRangeComponent->bIsEnemyInRange && TimeSinceLastShot >= ShootInterval)
        {
            Shoot();
            TimeSinceLastShot = 0.f;
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
            bool lvlUp = ((dir == 1) && (TowerLevel == 14 || TowerLevel == 10 || TowerLevel == 6 || TowerLevel == 3)) || ((dir == -1) && (TowerLevel == 15 || TowerLevel == 11 || TowerLevel == 7 || TowerLevel == 4 || TowerLevel == 1));
            UIScript->UpdateUI(dir, riverDist, lvlUp);
        }
    }
}