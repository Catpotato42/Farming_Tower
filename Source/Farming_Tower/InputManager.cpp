#include "InputManager.h"
#include "GameManager.h"
#include "AudioManager.h"


void AInputManager::BeginPlay()
{
    Super::BeginPlay();

    EnableInput(GetWorld()->GetFirstPlayerController());
    
    if (InputComponent)
        InputComponent->BindKey(EKeys::C, IE_Pressed, this, &AInputManager::AddCoins);

    if (InputComponent)
        InputComponent->BindKey(EKeys::N, IE_Pressed, this, &AInputManager::NextRound);
    if (InputComponent)
        InputComponent->BindKey(EKeys::M, IE_Pressed, this, &AInputManager::RoundPlus);
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

void AInputManager::RoundPlus()
{
    UGameManager* GameManager = GetGameInstance<UGameManager>();
    GameManager->round += 1;
    if (GameManager->canvas)
        GameManager->canvas->UpdateRound(GameManager->round);
}

void AInputManager::AddCoins()
{
    UGameManager* GameManager = GetGameInstance<UGameManager>();
    if (GameManager)
        GameManager->AddCoins(5);
}