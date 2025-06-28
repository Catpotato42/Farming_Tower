#pragma once

#include "CoreMinimal.h"
#include "IndicatorBase.h"
#include "MortarIndicator.generated.h"


UCLASS()
class FARMING_TOWER_API AMortarIndicator : public AIndicatorBase
{
	GENERATED_BODY()

public:
	virtual int IsGoodPlacement() override;
};
