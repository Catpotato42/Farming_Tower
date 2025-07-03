#pragma once

#include "CoreMinimal.h"
#include "FEnemySpawnInfo.h"
#include "FRoundInfo.generated.h"

USTRUCT(BlueprintType)
struct FRoundInfo
{
    GENERATED_BODY()

    // Enemies that should spawn in this round
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FEnemySpawnInfo> EnemiesToSpawn;
};
