
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlasterBeam.generated.h"

class UProjectileMovementComponent;

UCLASS()
class BADBOT_API ABlasterBeam : public AActor
{
	GENERATED_BODY()
	
public:	
	ABlasterBeam();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* BeamMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* ProjectileMovement;

private:	

};
