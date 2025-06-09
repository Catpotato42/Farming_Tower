#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ProjectileHoming.generated.h"

UCLASS()
class FARMING_TOWER_API AProjectileHoming : public AProjectileBase
{
    GENERATED_BODY()

public:
    void SetHomingTarget(AActor* Target);
};
