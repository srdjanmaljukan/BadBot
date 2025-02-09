
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlasterBeam.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

UCLASS()
class BADBOT_API ABlasterBeam : public AActor
{
	GENERATED_BODY()
	
public:	
	ABlasterBeam();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BeamMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UProjectileMovementComponent* ProjectileMovement;

	UFUNCTION()
	void OnBlasterHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* Explosion;

private:	

};
