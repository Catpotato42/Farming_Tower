#pragma once

#include "CoreMinimal.h"
#include "IndicatorBase.h"
#include "SniperIndicator.generated.h"


UCLASS()
class FARMING_TOWER_API ASniperIndicator : public AIndicatorBase
{
	GENERATED_BODY()
	
public:
	virtual int IsGoodPlacement() override;
};
