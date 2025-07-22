#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputManager.generated.h"

UCLASS()
class FARMING_TOWER_API AInputManager : public AActor
{
	GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent();
	
	void NextRound();
    void AddCoins();
    
    void ToggleRain();
    bool raining = false;
};
