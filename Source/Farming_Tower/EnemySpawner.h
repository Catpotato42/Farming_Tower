#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnInfo.h"
#include "RoundInfo.h"
#include "EnemySpawner.generated.h"

UCLASS()
class YOURGAME_API AEnemySpawner : public AActor
{
    GENERATED_BODY()

public:
    void StartRound(int currentRound);
    void NotifyEnemyKilled();

    UPROPERTY(EditAnywhere)
    TArray<FRoundInfo> RoundInfos;

    UPROPERTY(EditAnywhere)
    class UGameManager* gameManager;

private:
    int enemiesSpawnedThisRound = 0;
    int enemiesKilledThisRound = 0;

    void SpawnEnemy(TSubclassOf<AActor> enemyClass);
};
