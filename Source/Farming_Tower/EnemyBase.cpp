#include "EnemyBase.h"
#include "Components/SphereComponent.h"
#include "Components/SplineComponent.h"

AEnemyBase::AEnemyBase()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create and set the root collision component
    USphereComponent* SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
    RootComponent = SphereComp;
    SphereComp->InitSphereRadius(32.0f); // Optional: set collision radius
    SphereComp->SetCollisionProfileName(TEXT("Pawn")); // Or "OverlapAllDynamic" if needed

    UStaticMeshComponent* Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
    Mesh->SetupAttachment(RootComponent);

    // Load the engine's default sphere mesh and assign it
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    if (SphereMesh.Succeeded())
    {
        Mesh->SetStaticMesh(SphereMesh.Object);
    }

    Tags.Add(FName("Enemy"));
}


void AEnemyBase::SetPath(USplineComponent* InSpline)
{
    PathSpline = InSpline;
}

void AEnemyBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    MoveAlongPath(DeltaTime);
}

void AEnemyBase::BeginPlay()
{
    Super::BeginPlay();

    if (!PathSpline)
    {
        UE_LOG(LogTemp, Error, TEXT("Enemy has no spline path!"));
    }
}

void AEnemyBase::MoveAlongPath(float DeltaTime)
{
    if (!PathSpline) return;

    DistanceTravelled += Speed * DeltaTime;

    const float SplineLength = PathSpline->GetSplineLength();

    if (DistanceTravelled >= SplineLength)
    {
        OnReachedEnd();
        return;
    }

    FVector NewLocation = PathSpline->GetLocationAtDistanceAlongSpline(DistanceTravelled, ESplineCoordinateSpace::World);
    SetActorLocation(NewLocation);
}

void AEnemyBase::OnReachedEnd()
{
    //Attack/Notify decreased life
    Die();
}

void AEnemyBase::Die()
{
    if (Spawner)
    {
        Spawner->NotifyEnemyKilled();
    }

    Destroy();
}

void AEnemyBase::SetSpawner(AEnemySpawner* InSpawner)
{
    Spawner = InSpawner;
}