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
    TowerUI = FindComponentByClass<UWidgetComponent>();
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

    if (TowerUI)
    {
        FVector CameraLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation();
        FRotator LookAtRotation = (CameraLocation - TowerUI->GetComponentLocation()).Rotation();
        //LookAtRotation.Roll = 0.0f;
        FRotator ConstrainedRotation(0.f, LookAtRotation.Yaw, 0.f);
        TowerUI->SetWorldRotation(ConstrainedRotation);
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
    // Intentionally empty: subclasses should override this
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Base tower update called - override this."));
    UE_LOG(LogTemp, Warning, TEXT("Base tower update called - override this."));
}