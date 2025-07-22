#include "EnvironmentManager.h"


void AEnvironmentManager::RiverFlood()
{
    flooded = !flooded;
    for (AActor* Flood : FloodActors)
    {
		USceneComponent* RootComp = Flood->GetRootComponent();
		UPrimitiveComponent* RootPrim = Cast<UPrimitiveComponent>(Flood->GetRootComponent());
        if (RootComp && RootPrim)
        {
			UE_LOG(LogTemp, Warning, TEXT("Setting actor visible = %s"), flooded ? TEXT("true") : TEXT("false"));
            Flood->SetActorHiddenInGame(!flooded);
			RootComp->SetVisibility(flooded, true);
			if (flooded)
				RootPrim->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			else
				RootPrim->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
    }
}

