#pragma once

#include "CanvasManager.h"
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameManager.generated.h"


UCLASS()
class FARMING_TOWER_API UGameManager : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	//Coins
	UFUNCTION(BlueprintCallable)
	int32 GetCoins() const { return coins; }
	UFUNCTION(BlueprintCallable)
	void AddCoins(int n);
	UFUNCTION(BlueprintCallable)
	bool SpendCoins(int n);

	//Canvas
	UPROPERTY(BlueprintReadWrite)
	class UCanvasManager* canvas;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UCanvasManager> canvasPrefab;

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 coins;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 roundNumber;
};
