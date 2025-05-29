#include "GameManager.h"


void UGameManager::Init()
{
    Super::Init();

    if (canvasPrefab)
    {
        canvas = CreateWidget<UCanvasManager>(GetWorld(), canvasPrefab);
        if (IsValid(canvas))
            canvas->AddToViewport();
        else
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Canvas not created.");
    }
    coins = 0;
}


void UGameManager::AddCoins(int n)
{
    coins += n;
    if (IsValid(canvas))
        canvas->UpdateCoins(coins);
    else
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "CanvasManager is not valid! Cannot update coins.");
}

bool UGameManager::SpendCoins(int n)
{
    if (coins > n)
    {
        coins -= n;
        canvas->UpdateCoins(coins);
        return true;
    }
    else return false;
}