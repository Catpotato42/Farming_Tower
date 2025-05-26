// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerRange.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTowerRange::UTowerRange()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTowerRange::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTowerRange::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateClosestEnemy();
}

void UTowerRange::UpdateClosestEnemy()
{
	TArray<AActor*> FoundEnemies;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Enemy"), FoundEnemies);

	AActor* Owner = GetOwner();
	if (!Owner) return;

	FVector OwnerLocation = Owner->GetActorLocation();
	float ClosestDistanceSq = FLT_MAX;
	AActor* NearestEnemy = nullptr;

	for (AActor* Enemy : FoundEnemies)
	{
		if (!Enemy || Enemy == Owner) continue;

		FVector EnemyLocation = Enemy->GetActorLocation();

		// Only consider XY distance
		float DX = EnemyLocation.X - OwnerLocation.X;
		float DY = EnemyLocation.Y - OwnerLocation.Y;
		float DistanceSq = DX * DX + DY * DY;

		if (DistanceSq < ClosestDistanceSq)
		{
			ClosestDistanceSq = DistanceSq;
			NearestEnemy = Enemy;
		}
	}

	ClosestEnemy = NearestEnemy;
	bIsEnemyInRange = ClosestEnemy && FMath::Sqrt(ClosestDistanceSq) <= DetectionRange;

	if (GEngine)
	{
		if (ClosestEnemy)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green,
				FString::Printf(TEXT("Closest Enemy: %s"), *ClosestEnemy->GetName()));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, TEXT("No enemy in range."));
		}
	}
}

AActor* UTowerRange::GetClosestEnemy() const
{
	return ClosestEnemy;
}
