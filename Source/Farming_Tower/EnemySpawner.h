#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FEnemySpawnInfo.h"
#include "FRoundInfo.h"
#include "EnemySpawner.generated.h"

UCLASS()
class FARMING_TOWER_API AEnemySpawner : public AActor
{
    GENERATED_BODY()

public:
    // Constructor declaration
    AEnemySpawner();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

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

    UPROPERTY(VisibleAnywhere)
    USceneComponent* Root;
};
