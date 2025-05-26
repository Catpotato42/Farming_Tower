#include "GameManager.h"

bool UGameManager::SpendCoins(int n)
{
    if (coins > n)
    {
        coins -= n;
        return true;
    }
    else return false;
}