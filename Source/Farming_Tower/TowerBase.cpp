#include "TowerBase.h"
#include "TowerRange.h"

ATowerBase::ATowerBase()
{
    PrimaryActorTick.bCanEverTick = true;

    TowerRangeComponent = CreateDefaultSubobject<UTowerRange>(TEXT("TowerRangeComponent"));
}

void ATowerBase::BeginPlay()
{
    Super::BeginPlay();
}

void ATowerBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    TimeSinceLastShot += DeltaTime;

    if (TowerRangeComponent && TowerRangeComponent->bIsEnemyInRange && TimeSinceLastShot >= ShootInterval)
    {
        Shoot();
        TimeSinceLastShot = 0.0f;
    }
}

void ATowerBase::Shoot_Implementation()
{
    // Intentionally empty: subclasses should override this
    UE_LOG(LogTemp, Warning, TEXT("Base tower shoot called - override this in a child class."));
}
