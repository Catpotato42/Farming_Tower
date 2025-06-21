#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "TowerUI.generated.h"


UCLASS()
class FARMING_TOWER_API UTowerUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateLevel(int32 n);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* LevelText;
};
