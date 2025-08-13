#include "TowerRange.h"
#include "Enemies/EnemyBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTowerRange::UTowerRange()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTowerRange::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTowerRange::UpdateIsEnemyInRangeOnly()
{
	TArray<AActor*> FoundEnemies;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Enemy"), FoundEnemies);

	AActor* Owner = GetOwner();
	if (!Owner) return;

	FVector OwnerLocation = Owner->GetActorLocation();
	float EffectiveRangeSq = FMath::Square(DetectionRange + DetectionBuffer);
	bIsEnemyInRange = false;

	for (AActor* Enemy : FoundEnemies)
	{
		if (!Enemy || Enemy == Owner) continue;

		FVector EnemyLocation = Enemy->GetActorLocation();
		float DX = EnemyLocation.X - OwnerLocation.X;
		float DY = EnemyLocation.Y - OwnerLocation.Y;
		float DistanceSq = DX * DX + DY * DY;

		if (DistanceSq <= EffectiveRangeSq)
		{
			bIsEnemyInRange = true;
			return;
		}
	}
}

void UTowerRange::UpdateClosestEnemyToTower()
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
			//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red,
			//	FString::Printf(TEXT("No enemy in range. Closest enemy distance: %.2f (range %.2f)"),
			//		Distance, EffectiveRange));
		}
	}
}

AActor* UTowerRange::GetClosestEnemy() const
{
	return ClosestEnemy;
}

void UTowerRange::UpdateClosestEnemyToEnd()
{
	TArray<AActor*> FoundEnemies;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Enemy"), FoundEnemies);
	AActor* Owner = GetOwner();
	if (!Owner) return;

	AActor* FarthestEnemy = nullptr;
	float EffectiveRange = DetectionRange + DetectionBuffer;
	FVector OwnerLocation = Owner->GetActorLocation();
	float SmallestRemainingDist = FLT_MAX;
	AActor* BestCandidate = nullptr;


	for (AActor* Enemy : FoundEnemies)
	{
		if (!Enemy || Enemy == Owner) continue;

		FVector EnemyLocation = Enemy->GetActorLocation();

		float DX = EnemyLocation.X - OwnerLocation.X;
		float DY = EnemyLocation.Y - OwnerLocation.Y;
		float DistanceSq = DX * DX + DY * DY;

		if (DistanceSq > EffectiveRange * EffectiveRange) continue; // Only count enemy if it's actually within range plus buffer

		AEnemyBase* Typed = Cast<AEnemyBase>(Enemy);
		if (!Typed) continue;

		float Remaining = Typed->SplineLength - Typed->DistanceTraveled;

		if (Remaining < SmallestRemainingDist)
		{
			SmallestRemainingDist = Remaining;
			BestCandidate = Enemy;
		}
	}

	if (BestCandidate)
	{
		ClosestEnemyToEnd = BestCandidate;
	}
	else
	{
		ClosestEnemyToEnd = nullptr;
	}
}

AActor* UTowerRange::GetClosestEnemyToEnd() const
{
	return ClosestEnemyToEnd;
}

TArray<AActor*> UTowerRange::GetSortedEnemiesInRangeByEndProgress() const
{
	TArray<AActor*> FoundEnemies;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Enemy"), FoundEnemies);

	TArray<AActor*> SortedEnemies;
	AActor* Owner = GetOwner();
	if (!Owner) return SortedEnemies;

	const FVector OwnerLocation = Owner->GetActorLocation();
	const float EffectiveRangeSq = FMath::Square(DetectionRange + DetectionBuffer);

	TArray<TPair<float, AActor*>> Candidates;

	for (AActor* Enemy : FoundEnemies)
	{
		if (!Enemy || Enemy == Owner) continue;

		const FVector EnemyLocation = Enemy->GetActorLocation();
		const float DX = EnemyLocation.X - OwnerLocation.X;
		const float DY = EnemyLocation.Y - OwnerLocation.Y;
		const float DistanceSq = DX * DX + DY * DY;

		if (DistanceSq > EffectiveRangeSq) continue;

		AEnemyBase* Typed = Cast<AEnemyBase>(Enemy);
		if (!Typed) continue;

		const float Remaining = Typed->SplineLength - Typed->DistanceTraveled;
		Candidates.Add(TPair<float, AActor*>(Remaining, Enemy));
	}

	Candidates.Sort([](const TPair<float, AActor*>& A, const TPair<float, AActor*>& B)
	{
		return A.Key < B.Key;
	});

	for (const auto& Pair : Candidates)
	{
		SortedEnemies.Add(Pair.Value);
	}

	return SortedEnemies;
}

TArray<AActor*> UTowerRange::GetSortedEnemiesInRangeByHighestHealth() const
{
    TArray<AActor*> FoundEnemies;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Enemy"), FoundEnemies);

    TArray<AActor*> SortedEnemies;
    AActor* Owner = GetOwner();
    if (!Owner) return SortedEnemies;

    const FVector OwnerLocation = Owner->GetActorLocation();
    const float EffectiveRangeSq = FMath::Square(DetectionRange + DetectionBuffer);

    TArray<TPair<float, AActor*>> Candidates;

    for (AActor* Enemy : FoundEnemies)
    {
        if (!Enemy || Enemy == Owner) continue;

        const FVector EnemyLocation = Enemy->GetActorLocation();
        const float DX = EnemyLocation.X - OwnerLocation.X;
        const float DY = EnemyLocation.Y - OwnerLocation.Y;
        const float DistanceSq = DX * DX + DY * DY;

        if (DistanceSq > EffectiveRangeSq) continue;

        AEnemyBase* Typed = Cast<AEnemyBase>(Enemy);
        if (!Typed) continue;

        Candidates.Add(TPair<float, AActor*>(Typed->GetHealth(), Enemy));
    }

    // Sort descending (highest health first)
    Candidates.Sort([](const TPair<float, AActor*>& A, const TPair<float, AActor*>& B)
    {
        return A.Key > B.Key;
    });

    for (const auto& Pair : Candidates)
    {
        SortedEnemies.Add(Pair.Value);
    }

    return SortedEnemies;
}

TArray<AActor*> UTowerRange::GetSortedEnemiesInRangeByLowestHealth() const
{
    TArray<AActor*> FoundEnemies;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Enemy"), FoundEnemies);

    TArray<AActor*> SortedEnemies;
    AActor* Owner = GetOwner();
    if (!Owner) return SortedEnemies;

    const FVector OwnerLocation = Owner->GetActorLocation();
    const float EffectiveRangeSq = FMath::Square(DetectionRange + DetectionBuffer);

    TArray<TPair<float, AActor*>> Candidates;

    for (AActor* Enemy : FoundEnemies)
    {
        if (!Enemy || Enemy == Owner) continue;

        const FVector EnemyLocation = Enemy->GetActorLocation();
        const float DX = EnemyLocation.X - OwnerLocation.X;
        const float DY = EnemyLocation.Y - OwnerLocation.Y;
        const float DistanceSq = DX * DX + DY * DY;

        if (DistanceSq > EffectiveRangeSq) continue;

        AEnemyBase* Typed = Cast<AEnemyBase>(Enemy);
        if (!Typed) continue;

        Candidates.Add(TPair<float, AActor*>(Typed->GetHealth(), Enemy));
    }

    // Sort ascending (lowest health first)
    Candidates.Sort([](const TPair<float, AActor*>& A, const TPair<float, AActor*>& B)
    {
        return A.Key < B.Key;
    });

    for (const auto& Pair : Candidates)
    {
        SortedEnemies.Add(Pair.Value);
    }

    return SortedEnemies;
}