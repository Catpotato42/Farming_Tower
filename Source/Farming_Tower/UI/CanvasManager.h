#pragma once

#include "CoreMinimal.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Blueprint/UserWidget.h"
#include "CanvasManager.generated.h"


UCLASS()
class FARMING_TOWER_API UCanvasManager : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//tower UI
	void ShowTowerUI();
	void HideTowerUI();
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* TowerUI;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ShowTower;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* HideTower;
	
	//update values
	void UpdateCoins(int32 n);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CheckAvailibility();
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CoinsText;

	void UpdateRound(int32 n);
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* RoundText;

	void UpdateHealth(int32 n);
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HealthText;

	//weather forecast
	void SpawnWeatherIcon(FVector2D ScreenPosition, int index, bool start=false);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTexture2D*> WeatherPrefabs;
	UPROPERTY()
	TArray<UImage*> WeatherImages;
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* WeatherPanel;

	//time dilation
	UFUNCTION(BlueprintCallable)
	void SetAudioDilation();

	//game over
	UFUNCTION()
	void GameOver(int round);

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* GameOverUI;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* GameOverRounds;
};