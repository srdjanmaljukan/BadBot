
#include "BlasterBeam/BlasterBeam.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "Interfaces/Damageable.h"

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

	SetLifeSpan(5.f);
	
	if (BeamMesh)
	{
		BeamMesh->OnComponentHit.AddDynamic(this, &ABlasterBeam::OnBlasterHit);
	}
}

void ABlasterBeam::OnBlasterHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Explosion && OtherActor && OtherActor->GetClass()->ImplementsInterface(UDamageable::StaticClass()))
	{
		IDamageable::Execute_GetHurt(OtherActor, 10.f);
		FRotator ExplosionRotation = UKismetMathLibrary::MakeRotFromX(Hit.ImpactNormal);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Explosion, Hit.ImpactPoint, ExplosionRotation);
	}

	Destroy();
}

void ABlasterBeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

