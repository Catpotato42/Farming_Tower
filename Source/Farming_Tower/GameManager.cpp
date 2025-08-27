#include "GameManager.h"
#include "Towers/TowerBase.h"
#include "Components/AudioComponent.h"
#include "AudioManager.h"


void UGameManager::Init()
{
    Super::Init();
    SetupGame();
}

void UGameManager::SetupGame()
{
    coins = 20;
    round = 1;
    health = 20;
    setup = true;
}

void UGameManager::InitializeFirstIndicators()
{
    //This is called three separate times by each spawner but it's fine
    //Find enemy spawners
    TArray<AActor*> FoundSpawners;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), FoundSpawners);
    EnemySpawners.Empty();
    for (AActor* Actor : FoundSpawners)
    {
        AEnemySpawner* Spawner = Cast<AEnemySpawner>(Actor);
        if (Spawner)
        {
            EnemySpawners.Add(Spawner);
        }
    }
    //update spawner indicators
    for (AEnemySpawner* Spawner : EnemySpawners)
    {
        if (Spawner)
        {
            Spawner->CheckNextWaveEmpty(1);
        }
    }
}


void UGameManager::InitializeWeather()
{
    TArray<int> WeatherTypes = {0, 0, 0, 1, 2, 2};
    for (int i = 0; i < 6; i++)
    {
        canvas->SpawnWeatherIcon(FVector2D(i*132, 0), WeatherTypes[i], true);
    }
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

    //Find enemy spawners
    TArray<AActor*> FoundSpawners;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), FoundSpawners);
    EnemySpawners.Empty();
    FinishedSpawners.Empty();

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
    if (health > 0)
    {
        //update river flood
        if (!Environment)
        {
            TArray<AActor*> FoundEnvironments;
            UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnvironmentManager::StaticClass(), FoundEnvironments);
            if (FoundEnvironments.Num() > 0)
            {
                Environment = Cast<AEnvironmentManager>(FoundEnvironments[0]);
            }
        }
        if (Environment)
            canvas->SpawnWeatherIcon(FVector2D(660, 0), Environment->UpdateForecast());

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

        //update spawner indicators
        for (AEnemySpawner* Spawner : EnemySpawners)
        {
            if (Spawner)
            {
                Spawner->CheckNextWaveEmpty(round + 1); //Round is incremented after this, so make sure not to move that around.
            }
        }


        //Increment round
        setup = true;
        round++;
        canvas->UpdateRound(round);
        canvas->ShowTowerUI();
        if (AAudioManager::Instance)
        {
            AAudioManager::Instance->FadeBattle(false);
        }

        AddCoins(3);

        //re-enable start button
        canvas->EnableStartButton();
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
        canvas->GameOver(round);
    }
}

void UGameManager::OnSpawnerFinished(AEnemySpawner* Spawner)
{
    if (!FinishedSpawners.Contains(Spawner))
    {
        FinishedSpawners.Add(Spawner);
    }

    if (FinishedSpawners.Num() >= EnemySpawners.Num())
    {
        FinishedSpawners.Empty(); //Reset for next round
        EndRound();
    }
}