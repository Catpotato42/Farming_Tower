#include "CanvasManager.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"


void UCanvasManager::UpdateCoins(int32 n)
{
    if (CoinsText)
    {
        FString txt = FString::Printf(TEXT("Coins: %d"), n);
        CoinsText->SetText(FText::FromString(txt));
    }
}