#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Towers/TowerBase.h"
#include "TowerRange.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FARMING_TOWER_API UTowerRange : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTowerRange();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Targeting")
	void UpdateIsEnemyInRangeOnly();

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	void UpdateClosestEnemyToTower();

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	void UpdateClosestEnemyToEnd();

	// Returns the closest enemy actor
	UFUNCTION(BlueprintCallable, Category = "Targeting")
	AActor* GetClosestEnemy() const;

	// Returns the closest enemy actor to the end within range of the tower
	UFUNCTION(BlueprintCallable, Category = "Targeting")
	AActor* GetClosestEnemyToEnd() const;

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	TArray<AActor*> GetSortedEnemiesInRange(ETargetingMode SortMode = ETargetingMode::ClosestToEnd) const;

	// Indicates whether closest enemy is in range
	UPROPERTY(BlueprintReadOnly, Category = "Targeting")
	bool bIsEnemyInRange = false;

	// Settable range value (in cm)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	float DetectionRange = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	float DetectionBuffer = 25.0f;

private:

	AActor* ClosestEnemy = nullptr;

	AActor* ClosestEnemyToEnd = nullptr;
		
};
