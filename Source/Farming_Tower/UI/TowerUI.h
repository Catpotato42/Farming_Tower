#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "TowerUI.generated.h"

class ATowerBase;


UCLASS()
class FARMING_TOWER_API UTowerUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateLevel(int32 newLevel);
	void UpdateUI(int32 dir, int32 water, bool lvlUp);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* LevelText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* WaterText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* StateText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* LevelDir;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TargetModeText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* NextTargetModeButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* PrevTargetModeButton;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetOwningTower(ATowerBase* InTower);

	UFUNCTION(BlueprintCallable, Category="Targeting")
	void OnNextTargetMode();

	UFUNCTION(BlueprintCallable, Category="Targeting")
	void OnPreviousTargetMode();

	UFUNCTION(BlueprintCallable, Category="UI")
	void SetTargetModeText(const FText& NewText);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FLinearColor RedColor = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FLinearColor YellowColor = FLinearColor(0.8f, 0.8f, 0.1f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FLinearColor GreenColor = FLinearColor(0.1f, 1.0f, 0.2f, 1.0f);

private:
	//Probably shouldn't loop this reference back to TowerBase, but this is a new addition and I would have to rework the old stuff otherwise.
	UPROPERTY(BlueprintReadWrite, Category="UI", meta = (AllowPrivateAccess = "true"))
	ATowerBase* OwningTower;
};
