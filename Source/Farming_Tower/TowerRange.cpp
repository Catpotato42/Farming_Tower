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

	float Distance = FMath::Sqrt(ClosestDistanceSq);
	float DetectionBuffer = 25.0f;  // Adjust this buffer as needed
	
	// Only count enemy if it's actually within range plus buffer
	float EffectiveRange = DetectionRange + DetectionBuffer;
	if (NearestEnemy && Distance <= EffectiveRange)
	{
		ClosestEnemy = NearestEnemy;
		bIsEnemyInRange = true;

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green,
				FString::Printf(TEXT("Closest Enemy: %s | Distance: %.2f (within %.2f range)"),
					*ClosestEnemy->GetName(), Distance, EffectiveRange));
		}
	}
	else
	{
		ClosestEnemy = nullptr;
		bIsEnemyInRange = false;

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red,
				FString::Printf(TEXT("No enemy in range. Closest enemy distance: %.2f (range %.2f)"),
					Distance, EffectiveRange));
		}
	}
}

AActor* UTowerRange::GetClosestEnemy() const
{
	return ClosestEnemy;
}
