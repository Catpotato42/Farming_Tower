#include "CanvasManager.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"


void UCanvasManager::ShowTowerUI()
{
    if (TowerUI)
    {
        PlayAnimation(ShowTower);
        //TowerUI->SetVisibility(ESlateVisibility::Visible);
    }
}

void UCanvasManager::HideTowerUI()
{
    if (TowerUI)
    {
        PlayAnimation(HideTower);
        //TowerUI->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UCanvasManager::UpdateCoins(int32 n)
{
    if (CoinsText)
    {
        FString txt = FString::Printf(TEXT("Coins: %d"), n);
        CoinsText->SetText(FText::FromString(txt));
    }
}

void UCanvasManager::UpdateRound(int32 n)
{
    if (CoinsText)
    {
        FString txt = FString::Printf(TEXT("Round: %d"), n);
        RoundText->SetText(FText::FromString(txt));
    }
}