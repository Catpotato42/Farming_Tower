#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TowerPlacement.generated.h"


UCLASS()
class FARMING_TOWER_API ATowerPlacement : public APawn
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    void CancelPlacement();
};
