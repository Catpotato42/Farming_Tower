#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/WidgetInteractionComponent.h"
#include "TowerPlacement.generated.h"


UCLASS()
class FARMING_TOWER_API ATowerPlacement : public APawn
{
	GENERATED_BODY()

public:
    ATowerPlacement();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void Tick(float DeltaTime) override;
    virtual void BeginPlay() override;

    void PressWidget();
    void ReleaseWidget();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    void CancelPlacement();

	UFUNCTION(BlueprintCallable)
	int GetRiverDistance(FVector loc);

private:
	bool CheckRiverDistance(FVector loc, int distance);
    UPROPERTY(VisibleAnywhere)
    UWidgetInteractionComponent* WidgetInteraction;
};