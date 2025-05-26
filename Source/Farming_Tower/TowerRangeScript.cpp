// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerRangeScript.h"

// Sets default values for this component's properties
UTowerRangeScript::UTowerRangeScript()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTowerRangeScript::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTowerRangeScript::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//TODO: Replace void with Actor, as we are returning the actor that is closest to the tower
void UTowerRangeScript::ClosestEnemy () {
	
}

