#pragma once

#include "TowerPlacement.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IndicatorBase.generated.h"

UCLASS()
class FARMING_TOWER_API AIndicatorBase : public AActor
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable)
	virtual int IsGoodPlacement() { return 0; };
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ATowerPlacement* TowerPlacement;
};