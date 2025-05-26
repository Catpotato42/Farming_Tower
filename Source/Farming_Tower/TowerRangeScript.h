// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TowerRangeScript.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FARMING_TOWER_API UTowerRangeScript : public UActorComponent
{
	GENERATED_BODY()

private:
	void ClosestEnemy();

public:	
	// Sets default values for this component's properties
	UTowerRangeScript();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
