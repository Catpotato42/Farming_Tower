// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerBase.h"
#include "CattailTower.generated.h"

/**
 * 
 */
class AEnemyBase;
class AProjectileBeam;

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
    UFUNCTION()
    void OnBeamFinished();

private:
    UPROPERTY(EditAnywhere, Category = "Combat")
    TSubclassOf<AProjectileBeam> BeamProjectileClass;

    UPROPERTY()
    float BeamCooldownTimer = 0.f;

    UPROPERTY()
    AProjectileBeam* ActiveBeam = nullptr;

    UPROPERTY()
    AEnemyBase* CurrentTarget = nullptr;
};
