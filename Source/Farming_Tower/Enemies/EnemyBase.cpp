#include "EnemyBase.h"
#include "../GameManager.h"
#include "Components/SphereComponent.h"
#include "Components/SplineComponent.h"

AEnemyBase::AEnemyBase()
{
    PrimaryActorTick.bCanEverTick = true;

    Tags.Add(FName("Enemy"));
}


void AEnemyBase::SetPath(USplineComponent* InSpline)
{
    if (InSpline == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("SetPath called with null spline!"));
        return;
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("SetPath called with spline: %s"), *InSpline->GetName());
    }
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
}

void AEnemyBase::MoveAlongPath(float DeltaTime)
{
    if (!PathSpline) return;

    DistanceTraveled += Speed * DeltaTime;

    SplineLength = PathSpline->GetSplineLength();

    if (DistanceTraveled >= SplineLength)
    {
        OnReachedEnd();
        return;
    }

    FVector NewLocation = PathSpline->GetLocationAtDistanceAlongSpline(DistanceTraveled, ESplineCoordinateSpace::World);
    FVector Direction = PathSpline->GetDirectionAtDistanceAlongSpline(DistanceTraveled, ESplineCoordinateSpace::World);
    FRotator NewRotation = Direction.Rotation();
    SetActorRotation(NewRotation);
    SetActorLocation(NewLocation);
}

void AEnemyBase::OnReachedEnd()
{
    if (GameManager) {
        GameManager->DecreaseHealth(1);
    }
    
    DieNoCoins();
}

float AEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
    AController* EventInstigator, AActor* DamageCauser)
{
    ApplyDamage(DamageAmount);
    return DamageAmount;
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
    if (GameManager) {
        GameManager->AddCoins(CoinAmount);
    }

    Destroy();
}

void AEnemyBase::DieNoCoins()
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