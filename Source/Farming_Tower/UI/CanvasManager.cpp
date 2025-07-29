#include "CanvasManager.h"
#include "../AudioManager.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"

#include "Kismet/GameplayStatics.h"


void UCanvasManager::ShowTowerUI()
{
    if (TowerUI)
    {
        PlayAnimation(ShowTower);
    }
}

void UCanvasManager::HideTowerUI()
{
    if (TowerUI)
    {
        PlayAnimation(HideTower);
    }
}

void UCanvasManager::UpdateCoins(int32 n)
{
    if (CoinsText)
    {
        FString txt = FString::Printf(TEXT("Coins: %d"), n);
        CoinsText->SetText(FText::FromString(txt));
    }
    CheckAvailibility();
}

void UCanvasManager::UpdateRound(int32 n)
{
    if (CoinsText)
    {
        FString txt = FString::Printf(TEXT("Round: %d"), n);
        RoundText->SetText(FText::FromString(txt));
    }
}

void UCanvasManager::UpdateHealth(int32 n)
{
    if (HealthText)
    {
        FString txt = FString::Printf(TEXT("Health: %d"), n);
        HealthText->SetText(FText::FromString(txt));
    }
}


void UCanvasManager::SpawnWeatherIcon(FVector2D ScreenPosition, int index, bool start)
{
    UTexture2D* Texture = WeatherPrefabs.IsValidIndex(index) ? WeatherPrefabs[index] : nullptr;
    if (!WeatherPanel || !Texture)
        return;

    // Shift previous images
    if (!start)
    {
        if (WeatherImages.Num() > 0)
        {
            //WeatherImages[0]->RemoveFromParent();
            for (UImage* Image : WeatherImages)
            {
                if (Image)
                {
                    UCanvasPanelSlot* s = Cast<UCanvasPanelSlot>(Image->Slot);
                    if (s)
                    {
                        FVector2D Position = s->GetPosition();
                        Position.X -= 132; // Shift left
                        s->SetPosition(Position);
                    }
                }
            }
            WeatherImages.RemoveAt(0);
        }
    }

    // Create image widget
    UImage* NewImage = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
    if (!NewImage)
        return;

    // Set the brush texture
    NewImage->SetBrushFromTexture(Texture, true);

    // Add to canvas
    UCanvasPanelSlot* CanvasSlot = WeatherPanel->AddChildToCanvas(NewImage);
    if (CanvasSlot)
    {
        if (index == 0)
        {
            CanvasSlot->SetSize(FVector2D(125.f, 70.f));
            CanvasSlot->SetPosition(ScreenPosition + FVector2D(0, 3));
        }
        else if (index == 1)
        {
            CanvasSlot->SetSize(FVector2D(70.f, 60.f));
            CanvasSlot->SetPosition(ScreenPosition + FVector2D(30, 10));
        }
        else if (index == 2)
        {
            CanvasSlot->SetSize(FVector2D(105.f, 95.f));
            CanvasSlot->SetPosition(ScreenPosition + FVector2D(10, -8));
        }
    }
    WeatherImages.Add(NewImage);
}


void UCanvasManager::SetAudioDilation()
{
    if (AAudioManager::Instance)
    {
        AAudioManager::Instance->CustomTimeDilation = 1.0f / UGameplayStatics::GetGlobalTimeDilation(GetWorld());
    }
}