
#include "BlasterBeam/BlasterBeam.h"
#include "GameFramework/ProjectileMovementComponent.h"

ABlasterBeam::ABlasterBeam()
{
	PrimaryActorTick.bCanEverTick = true;

	BeamMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BeamMesh"));
	SetRootComponent(BeamMesh);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

void ABlasterBeam::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABlasterBeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

