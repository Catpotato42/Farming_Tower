#pragma once

#include "CoreMinimal.h"
#include "IndicatorBase.h"
#include "DaisyIndicator.generated.h"

UCLASS()
class FARMING_TOWER_API ADaisyIndicator : public AIndicatorBase
{
	GENERATED_BODY()
public:
	virtual int IsGoodPlacement() override;
};
