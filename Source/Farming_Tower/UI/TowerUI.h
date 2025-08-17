#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"

#include "TowerUI.generated.h"


UCLASS()
class FARMING_TOWER_API UTowerUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateLevel(int32 newLevel);
	void UpdateUI(int32 dir, int32 water, bool lvlUp, int elevation);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* LevelText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* WaterText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ElevationText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* StateText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* LevelDir;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCanvasPanel* HideDuringCombat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FLinearColor RedColor = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FLinearColor YellowColor = FLinearColor(0.8f, 0.8f, 0.1f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FLinearColor GreenColor = FLinearColor(0.1f, 1.0f, 0.2f, 1.0f);
};
