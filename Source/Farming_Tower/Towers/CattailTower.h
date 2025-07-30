// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Towers/TowerBase.h"
#include "CattailTower.generated.h"

/**
 * 
 */
class AEnemyBase;
class ABeamProjectile;

UCLASS()
class FARMING_TOWER_API ACattailTower : public ATowerBase
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;
    virtual void UpdateState() override;
    virtual int IsGoodPlacement() override;
	virtual void Shoot_Implementation() override;

	// Called by the beam when it is destroyed or stops firing
    void OnBeamFinished();

private:
    UPROPERTY(EditAnywhere, Category = "Combat")
    TSubclassOf<ABeamProjectile> BeamProjectileClass;

    UPROPERTY()
    ABeamProjectile* ActiveBeam = nullptr;

    UPROPERTY()
    AEnemyBase* CurrentTarget = nullptr;

	virtual void Tick(float DeltaTime) override;
};
