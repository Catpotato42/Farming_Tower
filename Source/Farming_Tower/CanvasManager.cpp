#include "CanvasManager.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"


void UCanvasManager::UpdateCoins(int32 n)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Coins: %d"), n));
    }
    UE_LOG(LogTemp, Warning, TEXT("Widget name is: %s"), *this->GetName());

    /*UTextBlock* CoinsText = Cast<UTextBlock>(WidgetTree->FindWidget("CoinsText"));
    if (CoinsText)
    {
        FString txt = FString::Printf(TEXT("Coins: %d"), n);
        CoinsText->SetText(FText::FromString(txt));
    }*/
}