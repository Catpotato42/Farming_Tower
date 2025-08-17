#include "TowerPlacement.h"
#include "Components/WidgetInteractionComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/WidgetComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATowerPlacement::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        EnableInput(PC);

        if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
        {
            // Bind Enhanced Input actions
            EnhancedInput->BindAction(LeftClickAction, ETriggerEvent::Started, this, &ATowerPlacement::PressWidget);
            EnhancedInput->BindAction(LeftClickAction, ETriggerEvent::Completed, this, &ATowerPlacement::ReleaseWidget);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("TowerPlacement has no EnhancedInputComponent!"));
        }

        // Add input mapping context to player
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(InputMappingContext, 0);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No PlayerController found in BeginPlay"));
    }
}

void ATowerPlacement::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!WidgetInteraction)
        return;

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        FHitResult Hit;
        if (PC->GetHitResultUnderCursor(ECC_Visibility, false, Hit))
        {
            WidgetInteraction->SetCustomHitResult(Hit);
        }
        else
        {
            WidgetInteraction->SetCustomHitResult(FHitResult());
        }
    }
}

// Widget interaction functions
void ATowerPlacement::PressWidget()
{
    if (WidgetInteraction)
        WidgetInteraction->PressPointerKey(EKeys::LeftMouseButton);
}

void ATowerPlacement::ReleaseWidget()
{
    if (WidgetInteraction)
        WidgetInteraction->ReleasePointerKey(EKeys::LeftMouseButton);
}


int ATowerPlacement::GetRiverDistance(FVector loc)
{
    if (CheckRiverDistance(loc, 0.3f))
    {
        return 0;
    }
    for (int i = 1; i < 10; i++)
    {
        if (CheckRiverDistance(loc, i))
        {
            return i;
        }
    }
    return 10;
}

bool ATowerPlacement::CheckRiverDistance(FVector loc, int distance)
{
    if (distance == 0)
    {
        FHitResult DownHit;
        FVector Start = loc + FVector(0, 0, 50);
        FVector End = loc - FVector(0, 0, 10000);

        FCollisionQueryParams Params;
        Params.AddIgnoredActor(this);

        while (GetWorld()->LineTraceSingleByChannel(DownHit, Start, End, ECC_Visibility, Params))
        {
            AActor* HitActor = DownHit.GetActor();
            if (!HitActor)
                break;

            if (HitActor->ActorHasTag("River"))
                return true;

            if (!HitActor->ActorHasTag("Tower"))
                break;

            Params.AddIgnoredActor(HitActor);
            Start = DownHit.ImpactPoint - FVector(0, 0, 1);
        }

        return false;
    }

    // Sphere check for distance > 0
    TArray<FHitResult> HitResults;
    FCollisionShape Sphere = FCollisionShape::MakeSphere(distance * 100);

    bool bHit = GetWorld()->SweepMultiByChannel(
        HitResults,
        loc,
        loc,
        FQuat::Identity,
        ECC_Pawn,
        Sphere
    );

    for (const FHitResult& Hit : HitResults)
    {
        if (Hit.GetActor() && Hit.GetActor()->ActorHasTag("River"))
            return true;
    }

    return false;
}