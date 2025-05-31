// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Returns the closest enemy actor
	UFUNCTION(BlueprintCallable, Category = "Targeting")
	AActor* GetClosestEnemy() const;

	// Indicates whether closest enemy is in range
	UPROPERTY(BlueprintReadOnly, Category = "Targeting")
	bool bIsEnemyInRange = false;

	// Settable range value (in cm)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	float DetectionRange = 100.f;

private:

	AActor* ClosestEnemy = nullptr;

	void UpdateClosestEnemy();
		
};
