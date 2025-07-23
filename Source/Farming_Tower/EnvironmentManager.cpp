#include "EnvironmentManager.h"


void AEnvironmentManager::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialize flood rounds
	floodRounds = FMath::RandRange(3, 6);
	WeatherForecast.Add("Sunny");
	WeatherForecast.Add("Sunny");
	WeatherForecast.Add("Sunny");
	WeatherForecast.Add("Half Flood");
	WeatherForecast.Add("Flood");
	WeatherForecast.Add("Flood");
}


int AEnvironmentManager::UpdateForecast()
{
	FString weather = WeatherForecast.IsValidIndex(0) ? WeatherForecast[0] : "Sunny";
	WeatherForecast.RemoveAt(0);
	if (weather == "Flood")
	{
		flooded = true;
		RiverFlood(false);
	}
	else if (weather == "Half Flood")
	{
		RiverFlood(true);
	}
	else
	{
		flooded = false;
		RiverFlood(false);
	}
	if (WeatherForecast[4] == "Half Flood") //complete transition to/from flood
	{
		if (WeatherForecast[3] == "Flood")
		{
			WeatherForecast.Add("Sunny");
			return 0;
		}
		else
		{
			WeatherForecast.Add("Flood");
			return 2;
		}
	}
	else if (WeatherForecast[4] == "Flood")
	{
		if (FMath::RandRange(1, 100) < 30) //30% to stop flooding
		{
			WeatherForecast.Add("Half Flood");
			return 1;
		}
		else
		{
			WeatherForecast.Add("Flood");
			return 2;
		}	
	}
	else if (WeatherForecast[4] == "Sunny")
	{
		if (FMath::RandRange(1, 100) < 20) //10% to start flooding
		{
			WeatherForecast.Add("Half Flood");
			return 1;
		}
		else
		{
			WeatherForecast.Add("Sunny");
			return 0;
		}
	}
	return 0;
}


void AEnvironmentManager::RiverFlood(bool half)
{    
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

