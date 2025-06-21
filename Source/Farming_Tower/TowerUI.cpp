#include "TowerUI.h"


void UTowerUI::UpdateLevel(int32 n)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Update level called");
    if (LevelText)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "LevelText is valid");
        LevelText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), n)));
    }
}