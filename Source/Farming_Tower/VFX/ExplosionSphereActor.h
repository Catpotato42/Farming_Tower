#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplosionSphereActor.generated.h"

UCLASS()
class FARMING_TOWER_API AExplosionSphereActor : public AActor
{
    GENERATED_BODY()

public:
    AExplosionSphereActor();

protected:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* SphereMesh;
};