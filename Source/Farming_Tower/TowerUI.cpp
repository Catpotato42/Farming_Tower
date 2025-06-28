#include "TowerUI.h"


void UTowerUI::UpdateLevel(int32 n)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Update Level: %d"), n));
    if (LevelText)
    {
        LevelText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), n)));
    }

    if (WaterText)
        WaterText->SetVisibility(ESlateVisibility::Hidden);
    if (StateText)
        StateText->SetVisibility(ESlateVisibility::Hidden);
    if (LevelDir)
        LevelDir->SetVisibility(ESlateVisibility::Hidden);
}


void UTowerUI::UpdateUI(int32 dir, int32 water)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Update UI: dir=%d, water=%d"), dir, water));
    if (WaterText)
        WaterText->SetVisibility(ESlateVisibility::Visible);
    if (StateText)
        StateText->SetVisibility(ESlateVisibility::Visible);
    if (LevelDir)
        LevelDir->SetVisibility(ESlateVisibility::Visible);

    if (WaterText)
        WaterText->SetText(FText::FromString(FString::Printf(TEXT("Water: %d"), water)));

    if (dir < 0)
    {
        StateText->SetText(FText::FromString(TEXT("Dying")));
        StateText->SetColorAndOpacity(FSlateColor(RedColor));
        LevelDir->SetText(FText::FromString(FString::Printf(TEXT("%d"), dir)));
        LevelDir->SetColorAndOpacity(FSlateColor(RedColor));
    }
    else if (dir > 0)
    {
        StateText->SetText(FText::FromString(TEXT("Growing")));
        StateText->SetColorAndOpacity(FSlateColor(GreenColor));
        LevelDir->SetText(FText::FromString(FString::Printf(TEXT("+%d"), dir)));
        LevelDir->SetColorAndOpacity(FSlateColor(GreenColor));
    }
    else
    {
        StateText->SetText(FText::FromString(TEXT("Stable")));
        StateText->SetColorAndOpacity(FSlateColor(YellowColor));
        LevelDir->SetText(FText::FromString(TEXT("")));
    }
}