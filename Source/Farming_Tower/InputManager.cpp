#include "InputManager.h"
#include "GameManager.h"


void AInputManager::BeginPlay()
{
    Super::BeginPlay();

    EnableInput(GetWorld()->GetFirstPlayerController());
    
    if (InputComponent)
        InputComponent->BindKey(EKeys::C, IE_Pressed, this, &AInputManager::AddCoins);
}

void AInputManager::SetupInputComponent() {}

void AInputManager::NextRound()
{
    UGameManager* GameManager = GetGameInstance<UGameManager>();
    if (GameManager->setup)
        GameManager->StartRound();
    else
        GameManager->EndRound();
}

void AInputManager::AddCoins()
{
    UGameManager* GameManager = GetGameInstance<UGameManager>();
    if (GameManager)
        GameManager->AddCoins(5);
}