#include "GameManager.h"


void UGameManager::Init()
{
    Super::Init();

    AEnemySpawner* Spawner = Cast<AEnemySpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AEnemySpawner::StaticClass()));
    coins = 0;
    round = 1;
    setup = true;
}


void UGameManager::StartRound()
{
    setup = false;
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Round started!"));
    canvas->HideTowerUI();

    if (enemySpawner)
        enemySpawner->StartRound(round);
}

void UGameManager::EndRound()
{
    setup = true;
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Ending round..."));
    round++;
    canvas->UpdateRound(round);
    canvas->ShowTowerUI();
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