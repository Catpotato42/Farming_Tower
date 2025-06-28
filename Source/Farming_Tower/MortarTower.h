#pragma once

#include "CoreMinimal.h"
#include "TowerBase.h"
#include "MortarTower.generated.h"


UCLASS()
class FARMING_TOWER_API AMortarTower : public ATowerBase
{
	GENERATED_BODY()
	
public:
	AMortarTower();
    virtual void UpdateState() override;
    virtual int IsGoodPlacement() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class AProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ProjectileSpeed = 1200.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float MaxProjectileDistance = 2000.f;
	
protected:
    virtual void Shoot_Implementation() override;
};