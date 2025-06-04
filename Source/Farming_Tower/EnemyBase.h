#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.h"
#include "EnemyBase.generated.h"


class USplineComponent;
class AEnemySpawner; // Forward declare your spawner class

UCLASS()
class FARMING_TOWER_API AEnemyBase : public AActor
{
    GENERATED_BODY()

public:
    AEnemyBase();

    virtual void Tick(float DeltaTime) override;
    virtual void BeginPlay() override;

    void SetPath(USplineComponent* InSpline);
    void SetSpawner(AEnemySpawner* InSpawner);

protected:
    UPROPERTY()
    USplineComponent* PathSpline;

    float DistanceTravelled = 0.0f;

    UPROPERTY(EditAnywhere, Category="Enemy")
    float Speed = 200.0f;

    UPROPERTY()
    AEnemySpawner* Spawner;

    void MoveAlongPath(float DeltaTime);
    void OnReachedEnd();
    void Die();
};
