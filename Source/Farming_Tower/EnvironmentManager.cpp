#include "EnvironmentManager.h"


void AEnvironmentManager::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialize flood rounds
	floodRounds = FMath::RandRange(3, 6);
}


void AEnvironmentManager::RiverFlood(bool half)
{
	if (!half)
	    flooded = !flooded;
    
	//half flood
	for (AActor* HalfFlood : HalfFloodActors)
    {
		USceneComponent* RootComp = HalfFlood->GetRootComponent();
		UPrimitiveComponent* RootPrim = Cast<UPrimitiveComponent>(HalfFlood->GetRootComponent());
        if (RootComp && RootPrim)
        {
            HalfFlood->SetActorHiddenInGame(!half);
			RootComp->SetVisibility(half, true);
			if (half)
				RootPrim->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			else
				RootPrim->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
    }
	
	//full flood
	for (AActor* Flood : FloodActors)
    {
		USceneComponent* RootComp = Flood->GetRootComponent();
		UPrimitiveComponent* RootPrim = Cast<UPrimitiveComponent>(Flood->GetRootComponent());
        if (RootComp && RootPrim)
        {
            Flood->SetActorHiddenInGame(!flooded || half);
			RootComp->SetVisibility(flooded && !half, true);
			if (flooded && !half)
				RootPrim->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			else
				RootPrim->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
    }

	if (!half)
	{
		if (flooded)
			floodRounds = FMath::RandRange(1, 4);
		else
			floodRounds = FMath::RandRange(4, 10);
	}
}

