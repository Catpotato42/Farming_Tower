#pragma once

#include "CoreMinimal.h"

#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Blueprint/UserWidget.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"  

#include "CanvasManager.generated.h"


UCLASS()
class FARMING_TOWER_API UCanvasManager : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct() override;

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
	UPROPERTY(BlueprintReadWrite)
	TArray<UImage*> WeatherImages;
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* WeatherPanel;

	//weather timeline
	/*FVector2D WeatherPosition;
	int WeatherIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UCurveFloat* MoveCurve;
	UPROPERTY()
	UTimelineComponent* MoveTimeline;
	
	FOnTimelineFloat TimelineProgress;
	UFUNCTION()
	void OnTimelineTick(float Value);

    FOnTimelineEvent TimelineFinished;
	UFUNCTION()
	void OnTimelineFinished();*/


	//time dilation
	UFUNCTION(BlueprintCallable)
	void SetAudioDilation();
};