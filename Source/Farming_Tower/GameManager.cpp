#include "GameManager.h"


void UGameManager::Init()
{
    Super::Init();

    /*if (canvasPrefab)
    {
        canvas = CreateWidget<UCanvasManager>(GetWorld(), canvasPrefab);
        if (IsValid(canvas))
        {
            canvas->AddToViewport();
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Canvas successful!");
        }
        else
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Canvas not created.");
    }*/
    coins = 0;
}


void UGameManager::AddCoins(int n)
{
    coins += n;
    canvas->UpdateCoins(coins);
}

bool UGameManager::SpendCoins(int n)
{
    if (coins >= n)
    {
        coins -= n;
        canvas->UpdateCoins(coins);
        return true;
    }
    else return false;
}