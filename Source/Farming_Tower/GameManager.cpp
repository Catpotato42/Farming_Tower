#include "GameManager.h"


void UGameManager::Init()
{
    Super::Init();

    coins = 0;
    round = 1;
    setup = true;
}


void UGameManager::StartRound()
{
    TArray<AActor*> FoundSpawners;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), FoundSpawners);
    EnemySpawners.Empty();

    for (AActor* Actor : FoundSpawners)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Found a spawner!"));
        AEnemySpawner* Spawner = Cast<AEnemySpawner>(Actor);
        if (Spawner)
        {
            EnemySpawners.Add(Spawner);
            Spawner->gameManager = this; // Set reference back to GameManager
        }
    }

    setup = false;
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Round started!"));
    canvas->HideTowerUI();

    for (AEnemySpawner* Spawner : EnemySpawners)
    {
        if (Spawner)
        {
            Spawner->StartRound(round);
        }
    }
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