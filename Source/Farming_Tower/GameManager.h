#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameManager.generated.h"


UCLASS()
class FARMING_TOWER_API UGameManager : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	int32 GetCoins() const { return coins; }
	UFUNCTION(BlueprintCallable)
	void SetCoins(int n) { coins=n; }
	UFUNCTION(BlueprintCallable)
	void AddCoins(int n) { coins += n; }
	UFUNCTION(BlueprintCallable)
	bool SpendCoins(int n);


private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 coins;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 roundNumber;
};
