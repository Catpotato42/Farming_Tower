#include "GameManager.h"


void UGameManager::Init()
{
    Super::Init();

    AEnemySpawner* Spawner = Cast<AEnemySpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AEnemySpawner::StaticClass()));
    coins = 0;
}


void UGameManager::StartRound()
{
    setup = false;
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Round started!"));
    //hide canvas elements

    if (enemySpawner)
        enemySpawner->StartRound(round);
}

void UGameManager::EndRound()
{
    setup = true;
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Ending round..."));
    round++;
    //update round text
    //show canvas elements
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