#include "GameManager.h"
#include "Towers/TowerBase.h"


void UGameManager::Init()
{
    Super::Init();

    coins = 20;
    round = 1;
    health = 20;
    setup = true;
}


void UGameManager::StartRound()
{
    //update towers
    TArray<AActor*> AllTowers;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Tower"), AllTowers);
    for (AActor* Actor : AllTowers)
    {
        ATowerBase* Tower = Cast<ATowerBase>(Actor);
        if (Tower)
        {
            Tower->UpdateState();
        }
    }

    //spawn enemies
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
    ATowerPlacement* TowerPawn = Cast<ATowerPlacement>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (TowerPawn)
    {
        TowerPawn->CancelPlacement();
    }

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
    //update towers
    TArray<AActor*> AllTowers;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Tower"), AllTowers);
    for (AActor* Actor : AllTowers)
    {
        ATowerBase* Tower = Cast<ATowerBase>(Actor);
        if (Tower)
        {
            Tower->UpdateTowerUI();
        }
    }

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

void UGameManager::DecreaseHealth(int n)
{
    health -= n;
    canvas->UpdateHealth(health);
    if (health <= 0)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Game Over!"));
        //show game over UI
    }
}