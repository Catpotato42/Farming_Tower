#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ProjectileHoming.generated.h"

UCLASS()
class FARMING_TOWER_API AProjectileHoming : public AProjectileBase
{
    GENERATED_BODY()

private:
    UPROPERTY(EditAnywhere)
    float HomingTurnSpeed = 5.0f;

    USceneComponent* HomingTarget = nullptr;

public:
    AProjectileHoming();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ProjectileSpeed = 3000.f;

    void SetHomingTarget(AActor* Target);
    virtual void Tick(float DeltaTime) override;
};
