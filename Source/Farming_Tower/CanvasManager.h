#pragma once

#include "CoreMinimal.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/UserWidget.h"
#include "CanvasManager.generated.h"


UCLASS()
class FARMING_TOWER_API UCanvasManager : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void ShowTowerUI();
	void HideTowerUI();
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* TowerUI;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ShowTower;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* HideTower;
	
	
	void UpdateCoins(int32 n);
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CoinsText;

	void UpdateRound(int32 n);
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* RoundText;
};