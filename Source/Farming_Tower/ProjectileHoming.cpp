#include "ProjectileHoming.h"
#include "GameFramework/ProjectileMovementComponent.h"

void AProjectileHoming::SetHomingTarget(AActor* Target)
{
    if (Target)
    {
        MovementComponent->bIsHomingProjectile = true;
        MovementComponent->HomingAccelerationMagnitude = 5000.0f;
        MovementComponent->HomingTargetComponent = Target->GetRootComponent();
    }
}
