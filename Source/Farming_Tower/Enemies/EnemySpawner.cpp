#include "EnemySpawner.h"
#include "TimerManager.h"
#include "EnemyBase.h"
#include "Logging/LogMacros.h"
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
    //could make like a sphere for now to see location
}

void AEnemySpawner::StartRound(int currentRound)
{
    PendingWaves.Empty();

    if (currentRound - 1 < RoundInfos.Num())
    {
        PendingWaves = RoundInfos[currentRound - 1].EnemiesToSpawn;
    }
    else
    {
        for (const auto& spawnInfo : RoundInfos.Last().EnemiesToSpawn)
        {
            FEnemySpawnInfo scaled = spawnInfo;
            scaled.Quantity += 2 + (currentRound - RoundInfos.Num());
            PendingWaves.Add(scaled);
        }
    }

    enemiesKilledThisRound = 0;
    CurrentWaveIndex = 0;
    EnemiesSpawnedInCurrentWave = 0;

    TotalEnemiesThisRound = 0;
    for (const auto& Info : PendingWaves)
    {
        TotalEnemiesThisRound += Info.Quantity;
    }
    UE_LOG(LogTemp, Warning, TEXT("Enemies in the round: %d"), TotalEnemiesThisRound);

    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemySpawner::SpawnNextEnemy, PendingWaves[0].InWaveWaitTime, true);
}

void AEnemySpawner::SpawnNextEnemy()
{
    if (CurrentWaveIndex >= PendingWaves.Num())
    {
        GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
        return;
    }

    FEnemySpawnInfo& wave = PendingWaves[CurrentWaveIndex];

    if (EnemiesSpawnedInCurrentWave < wave.Quantity)
    {
        SpawnEnemy(wave.EnemyClass);
        EnemiesSpawnedInCurrentWave++;
    }
    else
    { //finished the wave, go next
        CurrentWaveIndex++;
        EnemiesSpawnedInCurrentWave = 0;

        if (CurrentWaveIndex < PendingWaves.Num())
        {
            FEnemySpawnInfo& nextWave = PendingWaves[CurrentWaveIndex];
            FTimerHandle DelayHandle;
            GetWorld()->GetTimerManager().SetTimer(
                DelayHandle,
                [this]()
                {
                    if (CurrentWaveIndex < PendingWaves.Num())
                    {
                        FEnemySpawnInfo& currentWave = PendingWaves[CurrentWaveIndex];
                        GetWorld()->GetTimerManager().SetTimer(
                            SpawnTimerHandle,
                            this,
                            &AEnemySpawner::SpawnNextEnemy,
                            currentWave.InWaveWaitTime,
                            true
                        );
                    }
                },
                wave.AfterWaveWaitTime,
                false
            );
        }
        else
        {
            GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
        }
    }
}

void AEnemySpawner::SpawnEnemy(TSubclassOf<AEnemyBase> enemyClass)
{
    if (!enemyClass) return;

    FVector BaseLocation = GetActorLocation();

    // Doesn't work currently due to the spline path
    // Random offset within a radius
    float Radius = 500.f;
    FVector RandomOffset = FVector(
        FMath::RandRange(-Radius, Radius),
        FMath::RandRange(-Radius, Radius),
        0.f);

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
    UE_LOG(LogTemp, Warning, TEXT("Enemies killed this round: %d"), enemiesKilledThisRound);

    if (enemiesKilledThisRound >= TotalEnemiesThisRound && gameManager)
    {
        gameManager->EndRound();
    }
}