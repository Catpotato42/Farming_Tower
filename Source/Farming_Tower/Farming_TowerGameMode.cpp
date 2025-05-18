// Copyright Epic Games, Inc. All Rights Reserved.

#include "Farming_TowerGameMode.h"
#include "Farming_TowerPlayerController.h"
#include "Farming_TowerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFarming_TowerGameMode::AFarming_TowerGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AFarming_TowerPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}