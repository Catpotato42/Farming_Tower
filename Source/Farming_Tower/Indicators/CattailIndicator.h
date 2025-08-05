#pragma once

#include "CoreMinimal.h"
#include "IndicatorBase.h"
#include "CattailIndicator.generated.h"


UCLASS()
class FARMING_TOWER_API ACattailIndicator : public AIndicatorBase
{
	GENERATED_BODY()

public:
	virtual int IsGoodPlacement() override;
};
