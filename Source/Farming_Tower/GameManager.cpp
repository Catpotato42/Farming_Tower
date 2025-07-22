#include "GameManager.h"
#include "Towers/TowerBase.h"
#include "Components/AudioComponent.h"
#include "AudioManager.h"


void UGameManager::Init()
{
    Super::Init();

    coins = 500;
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
        AEnemySpawner* Spawner = Cast<AEnemySpawner>(Actor);
        if (Spawner)
        {
            EnemySpawners.Add(Spawner);
            Spawner->gameManager = this; // Set reference back to GameManager
        }
    }

    setup = false;
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
    if (AAudioManager::Instance)
    {
        AAudioManager::Instance->FadeBattle(true);
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
    round++;
    canvas->UpdateRound(round);
    canvas->ShowTowerUI();
    if (AAudioManager::Instance)
    {
        AAudioManager::Instance->FadeBattle(false);
    }

    if (FMath::RandRange(1, 100) <= 100)
    {
        if (!Environment)
        {
            TArray<AActor*> FoundEnvironments;
            UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnvironmentManager::StaticClass(), FoundEnvironments);
            if (GEngine)
            {
                FString DebugMsg = FString::Printf(TEXT("FoundEnvironments.Num() = %d"), FoundEnvironments.Num());
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, DebugMsg);
            }
            if (FoundEnvironments.Num() > 0)
            {
                Environment = Cast<AEnvironmentManager>(FoundEnvironments[0]);
            }
        }
        if (Environment)
        {
            UE_LOG(LogTemp, Warning, TEXT("RiverFlood called from GameManager"));
            Environment->RiverFlood();
        }
    }
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