#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnvironmentManager.generated.h"

UCLASS()
class FARMING_TOWER_API AEnvironmentManager : public AActor
{
	GENERATED_BODY()
	
public:	
	//river flood
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment")
	TArray<AActor*> FloodActors;
	bool flooded = false;
	void RiverFlood();
};
