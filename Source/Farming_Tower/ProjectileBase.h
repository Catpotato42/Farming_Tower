#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UCLASS()
class FARMING_TOWER_API AProjectileBase : public AActor
{
    GENERATED_BODY()

public:
    AProjectileBase();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    virtual void OnProjectileHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float Damage = 10.0f;

    UPROPERTY(VisibleAnywhere)
    class USphereComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere)
    class UProjectileMovementComponent* MovementComponent;
};
