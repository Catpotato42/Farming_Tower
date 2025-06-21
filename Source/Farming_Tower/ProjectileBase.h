#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "ProjectileBase.generated.h"

UCLASS()
class FARMING_TOWER_API AProjectileBase : public AActor
{
    GENERATED_BODY()

public:
    AProjectileBase();
    
protected:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    UFUNCTION()
    virtual void OnProjectileHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float Damage = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float Range = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    bool Gravity = false;  //Gravity on

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Setup")
    USphereComponent* MyCollisionComponent = nullptr;

    UPROPERTY(VisibleAnywhere)
    class UProjectileMovementComponent* MovementComponent;
private:
    FVector StartLocation;
};
