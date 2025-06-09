#include "EnemyBase.h"
#include "GameManager.h"
#include "Components/SphereComponent.h"
#include "Components/SplineComponent.h"

AEnemyBase::AEnemyBase()
{
    PrimaryActorTick.bCanEverTick = true;

    Tags.Add(FName("Enemy"));
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

    GameManager = Cast<UGameManager>(GetGameInstance());

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
    if (GameManager) {
        GameManager->DecreaseHealth(1);
    }
    
    Die();
}

void AEnemyBase::ApplyDamage(float DamageAmount)
{
    Health -= DamageAmount;
    if (Health <= 0.0f)
    {
        Die();
    }
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