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
	
protected:
    virtual void Shoot_Implementation() override;
};
