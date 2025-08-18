#include "TowerUI.h"
#include "../Towers/TowerBase.h"
#include "Engine/Engine.h"


void UTowerUI::UpdateLevel(int32 n)
{
    if (LevelText)
    {
        LevelText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), n)));
    }

    if (HideDuringCombat)
        HideDuringCombat->SetVisibility(ESlateVisibility::Hidden);
}


void UTowerUI::UpdateUI(int32 dir, int32 water, bool lvlUp, int32 altitude, bool dying)
{
    if (HideDuringCombat)
        HideDuringCombat->SetVisibility(ESlateVisibility::Visible);

    if (LevelDir)
    {
        if (lvlUp)
            LevelDir->SetVisibility(ESlateVisibility::Visible);
        else
            LevelDir->SetVisibility(ESlateVisibility::Hidden);
    }
    if (WaterText)
        WaterText->SetText(FText::FromString(FString::Printf(TEXT("%d"), water)));
    if (ElevationText)
        ElevationText->SetText(FText::FromString(FString::Printf(TEXT("%dm"), altitude)));

    if (dir < 0 && !dying)
    {
        StateText->SetText(FText::FromString(TEXT("Bad Environment")));
        StateText->SetColorAndOpacity(FSlateColor(RedColor));
        LevelDir->SetText(FText::FromString(FString::Printf(TEXT("%d"), dir)));
        LevelDir->SetColorAndOpacity(FSlateColor(RedColor));
    }
    else if (dying)
    {
        StateText->SetText(FText::FromString(TEXT("Dying (old)")));
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

void UTowerUI::SetTargetModeText(const FText& NewText)
{
    if (TargetModeText)
    {
        TargetModeText->SetText(NewText);
    }
}

void UTowerUI::OnNextTargetMode()
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("NextTargetMode clicked"));
    if (OwningTower)
    {
        OwningTower->NextTargetMode();
        OwningTower->UpdateTowerUI();
    }
}

void UTowerUI::OnPreviousTargetMode()
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("PrevTargetMode clicked"));
    if (OwningTower)
    {
        OwningTower->PreviousTargetMode();
        OwningTower->UpdateTowerUI();
    }
}

void UTowerUI::SetOwningTower(ATowerBase* InTower)
{
    OwningTower = InTower;

    /*if (TargetModeText)
    {
        if (OwningTower && OwningTower->SupportsTargetingModes())
        {
            TargetModeText->SetVisibility(ESlateVisibility::Visible);
            NextTargetModeButton->SetVisibility(ESlateVisibility::Visible);
            PrevTargetModeButton->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            TargetModeText->SetVisibility(ESlateVisibility::Collapsed);
            NextTargetModeButton->SetVisibility(ESlateVisibility::Collapsed);
            PrevTargetModeButton->SetVisibility(ESlateVisibility::Collapsed);
        }
        if (NextTargetModeButton)
            NextTargetModeButton->OnClicked.AddDynamic(this, &UTowerUI::OnNextTargetMode);

        if (PrevTargetModeButton)
            PrevTargetModeButton->OnClicked.AddDynamic(this, &UTowerUI::OnPreviousTargetMode);
    }*/
}