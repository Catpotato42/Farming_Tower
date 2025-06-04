#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "PathSplineActor.generated.h"

UCLASS()
class FARMING_TOWER_API APathSplineActor : public AActor
{
    GENERATED_BODY()

public:
    APathSplineActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    USplineComponent* SplineComponent;
};
