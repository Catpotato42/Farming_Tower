// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerBase.h"
#include "SniperTower.generated.h"

/**
 * 
 */
UCLASS()
class FARMING_TOWER_API ASniperTower : public ATowerBase
{
	GENERATED_BODY()
public:
	ASniperTower();
    virtual void UpdateState() override;
    virtual int IsGoodPlacement() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class AProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ProjectileSpeed = 3000.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float MaxProjectileDistance = 2000.f;
	
protected:
    virtual void Shoot_Implementation() override;
};
