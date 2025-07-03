#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FEnemySpawnInfo.h"
#include "FRoundInfo.h"
#include "PathSplineActor.h"
#include "EnemySpawner.generated.h"

class AEnemyBase;

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

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    APathSplineActor* AssignedPath;


private:
    int enemiesSpawnedThisRound = 0;
    int enemiesKilledThisRound = 0;

    TArray<TSubclassOf<AEnemyBase>> EnemiesToSpawnQueue;
    int32 CurrentSpawnIndex = 0;
    FTimerHandle SpawnTimerHandle;
    float SpawnInterval = 0.5f;

    void SpawnNextEnemy();
    void SpawnEnemy(TSubclassOf<AEnemyBase> enemyClass);

    UPROPERTY(VisibleAnywhere)
    USceneComponent* Root;
};
