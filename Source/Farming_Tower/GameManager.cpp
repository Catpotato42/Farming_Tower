#include "GameManager.h"


void UGameManager::Init()
{
    Super::Init();

    if (canvasPrefab)
    {
        canvas = CreateWidget<UCanvasManager>(this, canvasPrefab);
        if (canvas)
        {
            canvas->AddToViewport();
        }
    }
    coins = 0;
}


void UGameManager::AddCoins(int n)
{
    coins += n;
    canvas->UpdateCoins(coins);
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