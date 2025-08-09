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
    FVector WaitTime;

    FEnemySpawnInfo()
        : EnemyClass(nullptr), Quantity(0), WaitTime(0.f, 0.4f, 0.f) {}
};
