#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CanvasManager.generated.h"


UCLASS()
class FARMING_TOWER_API UCanvasManager : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateCoins(int n);
	
	//UPROPERTY(meta = (BindWidget))
	//UTextBlock* CoinsText;
	
};
