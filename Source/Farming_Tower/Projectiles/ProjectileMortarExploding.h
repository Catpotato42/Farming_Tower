#pragma once

#include "CoreMinimal.h"
#include "ProjectileMortar.h"
#include "ProjectileMortarExploding.generated.h"

/**
 * 
 */
UCLASS()
class FARMING_TOWER_API AProjectileMortarExploding : public AProjectileMortar
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float ExplosionRadius = 0.0f;

protected:
	virtual void OnProjectileHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

};
