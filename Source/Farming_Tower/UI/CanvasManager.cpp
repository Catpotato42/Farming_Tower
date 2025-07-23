#include "CanvasManager.h"
#include "../AudioManager.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"

#include "Kismet/GameplayStatics.h"


/*void UCanvasManager::NativeConstruct()
{
    Super::NativeConstruct();

    MoveTimeline = NewObject<UTimelineComponent>(this, TEXT("MoveTimeline"));
    MoveTimeline->RegisterComponent();
    MoveTimeline->PrimaryComponentTick.bCanEverTick = true;

    TimelineProgress.BindUFunction(this, FName("OnTimelineTick"));
    TimelineFinished.BindUFunction(this, FName("TimelineFinished"));

    if (MoveCurve)
    {
        MoveTimeline->AddInterpFloat(MoveCurve, TimelineProgress);
        MoveTimeline->SetTimelineFinishedFunc(TimelineFinished);
        MoveTimeline->SetLooping(false);
    }
}*/



//edit canvas values

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



//weather forecast

void UCanvasManager::SpawnWeatherIcon(FVector2D position, int index, bool skipMove)
{
    WeatherPosition = position;
    WeatherIndex = index;

    // Shift previous images
    if (MoveTimeline && !skipMove)
    {
        MoveTimeline->PlayFromStart();
    }
    else
    {
        OnTimelineFinished();
    }
}

/*void UCanvasManager::OnTimelineTick(float Value)
{
    if (WeatherImages.Num() > 0)
    {
        for (UImage* Image : WeatherImages)
        {
            if (Image)
            {
                UCanvasPanelSlot* s = Cast<UCanvasPanelSlot>(Image->Slot);
                if (s)
                {
                    FVector2D Position = s->GetPosition();
                    int startingX = WeatherImages.IndexOfByKey(Image)*132;
                    Position.X = FMath::Lerp(startingX, startingX - 132.f, Value);
                    s->SetPosition(Position);
                }
            }
        }
        WeatherImages.RemoveAt(0);
    }
}

void UCanvasManager::OnTimelineFinished()
{
    UE_LOG(LogTemp, Warning, TEXT("OnTimelineFinished"));
    UTexture2D* Texture = WeatherPrefabs.IsValidIndex(WeatherIndex) ? WeatherPrefabs[WeatherIndex] : nullptr;
    if (!WeatherPanel || !Texture)
        return;
    //WeatherImages[0]->RemoveFromParent();

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
        if (WeatherIndex == 0) //sun
        {
            CanvasSlot->SetSize(FVector2D(125.f, 70.f));
            CanvasSlot->SetPosition(WeatherPosition + FVector2D(0, 3));
        }
        else if (WeatherIndex == 1) //light rain
        {
            CanvasSlot->SetSize(FVector2D(70.f, 60.f));
            CanvasSlot->SetPosition(WeatherPosition + FVector2D(30, 10));
        }
        else if (WeatherIndex == 2) //rain
        {
            CanvasSlot->SetSize(FVector2D(105.f, 95.f));
            CanvasSlot->SetPosition(WeatherPosition + FVector2D(10, -8));
        }
    }
    WeatherImages.Add(NewImage);
}*/


void UCanvasManager::SetAudioDilation()
{
    if (AAudioManager::Instance)
    {
        AAudioManager::Instance->CustomTimeDilation = 1.0f / UGameplayStatics::GetGlobalTimeDilation(GetWorld());
    }
}