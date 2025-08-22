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
    AEnemySpawner();

    virtual void BeginPlay() override;

    void StartRound(int currentRound);
    void NotifyEnemyKilled();
    void CheckNextWaveEmpty(int nextRound);

    UPROPERTY(EditAnywhere)
    TArray<FRoundInfo> RoundInfos;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Indicators")
    UStaticMeshComponent* IndicatorArrowSpawnCube;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Indicators")
    UStaticMeshComponent* IndicatorArrowSpawnTri;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Indicators")
    UStaticMeshComponent* IndicatorArrowTurn1Cube;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Indicators")
    UStaticMeshComponent* IndicatorArrowTurn1Tri;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Indicators")
    UStaticMeshComponent* IndicatorArrowTurn2Cube;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Indicators")
    UStaticMeshComponent* IndicatorArrowTurn2Tri;

    UPROPERTY(EditAnywhere)
    class UGameManager* gameManager;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    APathSplineActor* AssignedPath;


private:
    int enemiesSpawnedThisRound = 0;
    int enemiesKilledThisRound = 0;

    TArray<FEnemySpawnInfo> PendingWaves;
    int32 CurrentWaveIndex = 0;
    int32 EnemiesSpawnedInCurrentWave = 0;
    int32 TotalEnemiesThisRound = 0;
    FTimerHandle SpawnTimerHandle;

    void SpawnNextEnemy();
    void SpawnEnemy(TSubclassOf<AEnemyBase> enemyClass);
    void ShowWaveIndicators(bool bShow);

    UPROPERTY(VisibleAnywhere)
    USceneComponent* Root;
};
