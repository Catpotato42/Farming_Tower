#pragma once

#include "CoreMinimal.h"
#include "IndicatorBase.h"
#include "CactusIndicator.generated.h"


UCLASS()
class FARMING_TOWER_API ACactusIndicator : public AIndicatorBase
{
	GENERATED_BODY()

public:
	virtual int IsGoodPlacement() override;
};
