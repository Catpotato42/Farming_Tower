#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "TowerPlacement.generated.h"

class UWidgetInteractionComponent;
class UInputMappingContext;
class UInputAction;


UCLASS()
class FARMING_TOWER_API ATowerPlacement : public APawn
{
	GENERATED_BODY()

public:
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

    UPROPERTY(EditAnywhere, Category="Input")
    UInputMappingContext* InputMappingContext;

    UPROPERTY(EditAnywhere, Category="Input")
    UInputAction* LeftClickAction;
};