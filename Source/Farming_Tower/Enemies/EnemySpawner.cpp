#include "EnemySpawner.h"
#include "TimerManager.h"
#include "EnemyBase.h"
#include "Logging/LogMacros.h"
#include "../GameManager.h"

#include "Kismet/GameplayStatics.h"

AEnemySpawner::AEnemySpawner()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;
}

void AEnemySpawner::BeginPlay()
{
    Super::BeginPlay();
    gameManager = Cast<UGameManager>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (!gameManager)
    {
        UE_LOG(LogTemp, Warning, TEXT("GameManager not found in EnemySpawner"));
    } else {
        gameManager->InitializeFirstIndicators();
    }
}

void AEnemySpawner::StartRound(int currentRound)
{
    PendingWaves.Empty();

    ShowWaveIndicators(false);

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
    if (PendingWaves.Num() > 0)
    {
        for (const auto& Info : PendingWaves)
        {
            TotalEnemiesThisRound += Info.Quantity;
        }
        UE_LOG(LogTemp, Log, TEXT("Before wave wait time: %f"), PendingWaves[0].WaitTime.X);
        GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemySpawner::SpawnNextEnemy, PendingWaves[0].WaitTime.Y, true, PendingWaves[0].WaitTime.X);
    }
    else
    {
        if (gameManager)
        {
            gameManager->OnSpawnerFinished(this);
        }
    }
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
    { // finished the wave, go next
        CurrentWaveIndex++;
        EnemiesSpawnedInCurrentWave = 0;

        if (CurrentWaveIndex < PendingWaves.Num())
        {
            // Clear the spawn timer
            GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);

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
                            currentWave.WaitTime.Y,
                            true
                        );
                    }
                },
                wave.WaitTime.Z + PendingWaves[CurrentWaveIndex].WaitTime.X, // wait time before starting next wave
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
    if (enemiesKilledThisRound >= TotalEnemiesThisRound && gameManager)
    {
        gameManager->OnSpawnerFinished(this);
    }
}

void AEnemySpawner::CheckNextWaveEmpty(int nextRound)
{
    if (nextRound - 1 < RoundInfos.Num())
    {
        ShowWaveIndicators(RoundInfos[nextRound - 1].EnemiesToSpawn.Num() > 0);
    }
    else {
        ShowWaveIndicators(RoundInfos.Last().EnemiesToSpawn.Num() > 0);
        //TODO: if all infinite waves will have enemies in them (I assume they eventually will), just show indicators forever after.
        //ShowWaveIndicators(true);
    }
}

void AEnemySpawner::ShowWaveIndicators(bool bShow)
{
    if (bShow) {
        UE_LOG(LogTemp, Log, TEXT("Showing wave indicators for enemy spawner: %s"), *GetName());
    }
    IndicatorArrowSpawnCube->SetVisibility(bShow);
    IndicatorArrowSpawnTri->SetVisibility(bShow);
    IndicatorArrowTurn1Cube->SetVisibility(bShow);
    IndicatorArrowTurn1Tri->SetVisibility(bShow);
    IndicatorArrowTurn2Cube->SetVisibility(bShow);
    IndicatorArrowTurn2Tri->SetVisibility(bShow);
}