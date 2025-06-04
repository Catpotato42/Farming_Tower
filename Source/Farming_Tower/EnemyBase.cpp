#include "EnemyBase.h"
#include "Components/SplineComponent.h"

AEnemyBase::AEnemyBase()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AEnemyBase::SetPath(USplineComponent* InSpline)
{
    PathSpline = InSpline;
}

void AEnemyBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    MoveAlongPath(DeltaTime);
}

void AEnemyBase::BeginPlay()
{
    Super::BeginPlay();

    if (!PathSpline)
    {
        UE_LOG(LogTemp, Error, TEXT("Enemy has no spline path!"));
    }
}

void AEnemyBase::MoveAlongPath(float DeltaTime)
{
    if (!PathSpline) return;

    DistanceTravelled += Speed * DeltaTime;

    const float SplineLength = PathSpline->GetSplineLength();

    if (DistanceTravelled >= SplineLength)
    {
        OnReachedEnd();
        return;
    }

    FVector NewLocation = PathSpline->GetLocationAtDistanceAlongSpline(DistanceTravelled, ESplineCoordinateSpace::World);
    SetActorLocation(NewLocation);
}

void AEnemyBase::OnReachedEnd()
{
    Die(); // Or just Destroy()
}

void AEnemyBase::Die()
{
    if (Spawner)
    {
        Spawner->NotifyEnemyKilled();
    }

    Destroy();
}

void AEnemyBase::SetSpawner(AEnemySpawner* InSpawner)
{
    Spawner = InSpawner;
}