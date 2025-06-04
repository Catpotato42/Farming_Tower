#pragma once

#include "CoreMinimal.h"
#include "FEnemySpawnInfo.generated.h"

USTRUCT(BlueprintType)
struct FEnemySpawnInfo
{
    GENERATED_BODY()

    // Which type of enemy to spawn
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> EnemyClass;

    // How many of them to spawn
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Quantity;

    FEnemySpawnInfo()
        : EnemyClass(nullptr), Quantity(0) {}
};
