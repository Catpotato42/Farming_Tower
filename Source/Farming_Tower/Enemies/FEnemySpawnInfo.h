#pragma once

#include "CoreMinimal.h"
#include "FEnemySpawnInfo.generated.h"

class AEnemyBase;

USTRUCT(BlueprintType)
struct FEnemySpawnInfo
{
    GENERATED_BODY()

    // Which type of enemy to spawn
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AEnemyBase> EnemyClass;

    // How many of them to spawn
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Quantity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float InWaveWaitTime;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AfterWaveWaitTime;

    FEnemySpawnInfo()
        : EnemyClass(nullptr), Quantity(0), InWaveWaitTime(0.4f), AfterWaveWaitTime(1.0f) {}
};
