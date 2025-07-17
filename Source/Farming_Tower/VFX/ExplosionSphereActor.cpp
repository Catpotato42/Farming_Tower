#include "ExplosionSphereActor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AExplosionSphereActor::AExplosionSphereActor()
{
    UE_LOG(LogTemp, Warning, TEXT("ExplosionSphereActor spawned!"));
    SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
    RootComponent = SphereMesh;
	SphereMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    if (SphereMeshAsset.Succeeded())
    {
        SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
    }
    else 
    {
        UE_LOG(LogTemp, Warning, TEXT("Sphere mesh asset not found! (ExplosionSphereActor)"));
    }

    // Optionally set a white material (replace with your own if needed)
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> WhiteMaterialAsset(TEXT("/Engine/BasicShapes/BasicShapeMaterial"));
    if (WhiteMaterialAsset.Succeeded())
    {
        SphereMesh->SetMaterial(0, WhiteMaterialAsset.Object);
    }
    else 
    {
        UE_LOG(LogTemp, Warning, TEXT("White material asset not found! (ExplosionSphereActor)"));
    }
}
