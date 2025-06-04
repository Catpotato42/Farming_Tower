#pragma once

#include "CanvasManager.h"
#include "EnemySpawner.h"
#include "TowerPlacement.h"

#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "GameManager.generated.h"



UCLASS()
class FARMING_TOWER_API UGameManager : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	//Game State
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 round;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool setup;
	UFUNCTION(BlueprintCallable)
	void StartRound();
	UFUNCTION(BlueprintCallable)
	void EndRound();

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

	//Enemies
	UPROPERTY(EditDefaultsOnly, Category = "Enemies")
	TArray<AEnemySpawner*> EnemySpawners;


private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 coins;
};
