#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnvironmentManager.generated.h"

UCLASS()
class FARMING_TOWER_API AEnvironmentManager : public AActor
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;

	UPROPERTY()
	TArray<FString> WeatherForecast;
	int UpdateForecast();

	int stopFloodChance = 60;
	int startFloodChance = 5;

	//river flood
	void RiverFlood(bool half);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment")
	TArray<AActor*> FloodActors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment")
	TArray<AActor*> HalfFloodActors;

	bool flooded = false;
	int floodRounds;
};
