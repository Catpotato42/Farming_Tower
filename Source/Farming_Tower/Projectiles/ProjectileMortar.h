// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ProjectileMortar.generated.h"

/**
 * 
 */
UCLASS()
class FARMING_TOWER_API AProjectileMortar : public AProjectileBase
{
	GENERATED_BODY()
	
public:
	void LaunchTowardsTarget(const FVector& Start, const FVector& Target, float ArcHeight);
};
