#include "EnemySpawner.h"
#include "TimerManager.h"
#include "EnemyBase.h"
#include "../GameManager.h"

#include "Kismet/GameplayStatics.h"

void AEnemySpawner::BeginPlay()
{
    Super::BeginPlay();
}

AEnemySpawner::AEnemySpawner()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    // Optional: add visual/debug component so you can see it
}

void AEnemySpawner::StartRound(int currentRound)
{
    EnemiesToSpawnQueue.Empty();

    TArray<FEnemySpawnInfo> toSpawn;
    if (currentRound - 1 < RoundInfos.Num())
    {
        toSpawn = RoundInfos[currentRound - 1].EnemiesToSpawn;
    }
    else
    {
        for (const auto& spawnInfo : RoundInfos.Last().EnemiesToSpawn)
        {
            FEnemySpawnInfo scaled = spawnInfo;
            scaled.Quantity += 2 + (currentRound - RoundInfos.Num());
            toSpawn.Add(scaled);
        }
    }

    for (const auto& enemyInfo : toSpawn)
    {
        for (int i = 0; i < enemyInfo.Quantity; ++i)
        {
            EnemiesToSpawnQueue.Add(enemyInfo.EnemyClass);  // Add just the class, no struct here
        }
    }

    enemiesKilledThisRound = 0;
    CurrentSpawnIndex = 0;

    // Start the spawn timer
    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemySpawner::SpawnNextEnemy, SpawnInterval, true);
}

void AEnemySpawner::SpawnNextEnemy()
{
    if (CurrentSpawnIndex >= EnemiesToSpawnQueue.Num())
    {
        GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
        return;
    }

    TSubclassOf<AEnemyBase> EnemyClass = EnemiesToSpawnQueue[CurrentSpawnIndex];
    SpawnEnemy(EnemyClass);

    CurrentSpawnIndex++;
}

void AEnemySpawner::SpawnEnemy(TSubclassOf<AEnemyBase> enemyClass)
{
    if (!enemyClass) return;

    FVector BaseLocation = GetActorLocation();

    // Random offset within a radius, e.g. 100 units
    float Radius = 100.f;
    FVector RandomOffset = FVector(
        FMath::RandRange(-Radius, Radius),
        FMath::RandRange(-Radius, Radius),
        0.f);  // Keep Z constant

    FVector SpawnLocation = BaseLocation + RandomOffset;

    FActorSpawnParameters spawnParams;
    AActor* spawned = GetWorld()->SpawnActor<AActor>(enemyClass, SpawnLocation, FRotator::ZeroRotator, spawnParams);

    if (AEnemyBase* enemy = Cast<AEnemyBase>(spawned))
    {
        enemy->SetSpawner(this);
        
        if (AssignedPath)
        {
            enemy->SetPath(AssignedPath->SplineComponent);
        }
    }

}

void AEnemySpawner::NotifyEnemyKilled()
{
    enemiesKilledThisRound++;

    if (enemiesKilledThisRound >= EnemiesToSpawnQueue.Num() && gameManager)
    {
        gameManager->EndRound();
    }
}