// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioManager.generated.h"

UCLASS()
class FARMING_TOWER_API AAudioManager : public AActor
{
	GENERATED_BODY()
	
public:	
	static AAudioManager* Instance;
	void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void FadeBattle(bool in);

	UFUNCTION(BlueprintImplementableEvent)
	void FadeSun(bool in);

	UFUNCTION(BlueprintImplementableEvent)
	void FadeLightRain(bool in);

	UFUNCTION(BlueprintImplementableEvent)
	void FadeRain(bool in);

	UFUNCTION(BlueprintImplementableEvent)
	void FadeBase(bool in);
};
