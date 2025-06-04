#include "InputManager.h"
#include "GameManager.h"


void AInputManager::BeginPlay()
{
    Super::BeginPlay();

    EnableInput(GetWorld()->GetFirstPlayerController());
    
    if (InputComponent)
        InputComponent->BindKey(EKeys::N, IE_Pressed, this, &AInputManager::NextRound);
}


void AInputManager::NextRound()
{
    UGameManager* GameManager = GetGameInstance<UGameManager>();
    if (GameManager->setup)
        GameManager->StartRound();
    else
        GameManager->EndRound();       
}