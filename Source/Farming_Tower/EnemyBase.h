#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.h"
#include "EnemyBase.generated.h"

class UGameManager;
class USplineComponent;
class AEnemySpawner; // Forward declare spawner class

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

    UFUNCTION()
    void ApplyDamage(float DamageAmount);

protected:
    UPROPERTY()
    USplineComponent* PathSpline;

    float DistanceTravelled = 0.0f;

    UPROPERTY(EditAnywhere, Category="Enemy")
    float Speed = 200.0f;

    UPROPERTY(EditAnywhere, Category = "Enemy")
    TSubclassOf<AEnemyBase> EnemyToSpawn;

    UPROPERTY(EditAnywhere, Category = "Enemy")
    float Health = 50.0f;

    UPROPERTY()
    UGameManager* GameManager;

    UPROPERTY()
    AEnemySpawner* Spawner;

    void MoveAlongPath(float DeltaTime);
    void OnReachedEnd();
    void Die();
};
