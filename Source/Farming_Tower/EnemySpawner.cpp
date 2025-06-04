#include "EnemySpawner.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyBase.h"
#include "GameManager.h"

void AEnemySpawner::StartRound(int currentRound)
{
    TArray<FEnemySpawnInfo> toSpawn;

    if (currentRound - 1 < RoundInfos.Num())
    {
        toSpawn = RoundInfos[currentRound - 1].EnemiesToSpawn;
    }
    else
    {
        // Infinite scaling
        for (const auto& spawnInfo : RoundInfos.Last().EnemiesToSpawn)
        {
            FEnemySpawnInfo scaled = spawnInfo;
            scaled.Quantity += 2 * (currentRound - RoundInfos.Num());
            toSpawn.Add(scaled);
        }
    }

    enemiesSpawnedThisRound = 0;
    enemiesKilledThisRound = 0;

    for (const auto& enemyInfo : toSpawn)
    {
        for (int i = 0; i < enemyInfo.Quantity; ++i)
        {
            GetWorld()->GetTimerManager().SetTimerForNextTick([this, enemyInfo]()
            {
                SpawnEnemy(enemyInfo.EnemyClass);
            });
            enemiesSpawnedThisRound++;
        }
    }
}

void AEnemySpawner::SpawnEnemy(TSubclassOf<AActor> enemyClass)
{
    if (!enemyClass) return;

    FActorSpawnParameters spawnParams;
    AActor* spawned = GetWorld()->SpawnActor<AActor>(enemyClass, GetActorLocation(), FRotator::ZeroRotator, spawnParams);

    if (AEnemyBase* enemy = Cast<AEnemyBase>(spawned))
    {
        enemy->SetSpawner(this);
    }
}

void AEnemySpawner::NotifyEnemyKilled()
{
    enemiesKilledThisRound++;

    if (enemiesKilledThisRound >= enemiesSpawnedThisRound && gameManager)
    {
        gameManager->EndRound();
    }
}

void AEnemyBase::SetSpawner(AEnemySpawner* InSpawner)
{
    Spawner = InSpawner;
}