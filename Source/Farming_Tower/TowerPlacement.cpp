#include "TowerPlacement.h"
#include "Components/WidgetInteractionComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

ATowerPlacement::ATowerPlacement()
{
    PrimaryActorTick.bCanEverTick = true;
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    WidgetInteraction = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteraction"));
    WidgetInteraction->InteractionDistance = 100000.f; // far enough
    WidgetInteraction->InteractionSource = EWidgetInteractionSource::Mouse; // mouse input
    WidgetInteraction->bShowDebug = true;
}

void ATowerPlacement::BeginPlay()
{
    Super::BeginPlay();
    EnableInput(GetWorld()->GetFirstPlayerController());
}

void ATowerPlacement::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    UE_LOG(LogTemp, Warning, TEXT("Called SetupPlayerInputComponent"));

    PlayerInputComponent->BindAction("LeftClick", IE_Pressed, this, &ATowerPlacement::PressWidget);
    PlayerInputComponent->BindAction("LeftClick", IE_Released, this, &ATowerPlacement::ReleaseWidget);
}

void ATowerPlacement::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        FHitResult Hit;
        if (PC->GetHitResultUnderCursor(ECC_Visibility, false, Hit))
        {
            if (WidgetInteraction)
                WidgetInteraction->SetCustomHitResult(Hit);
            else
                UE_LOG(LogTemp, Warning, TEXT("WidgetInteraction is null in Tick"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("No hit under cursor in Tick"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Pawn does not have a PlayerController in Tick"));
    }
}

void ATowerPlacement::PressWidget()
{
    if (WidgetInteraction)
    {
        WidgetInteraction->PressPointerKey(EKeys::LeftMouseButton);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("WidgetInteraction is null in PressWidget"));
    }
}

void ATowerPlacement::ReleaseWidget()
{
    if (WidgetInteraction)
    {
        WidgetInteraction->ReleasePointerKey(EKeys::LeftMouseButton);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("WidgetInteraction is null in ReleaseWidget"));
    }
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