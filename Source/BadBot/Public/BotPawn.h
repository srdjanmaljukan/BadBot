// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "Interfaces/Damageable.h"
#include "BotPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UFloatingPawnMovement;
class UInputMappingContext;
class UInputAction;
class ABlasterBeam;
class UNiagaraSystem;
class USoundBase;

UCLASS()
class BADBOT_API ABotPawn : public APawn, public IDamageable
{
	GENERATED_BODY()

public:
	ABotPawn();

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetHurt_Implementation(float DamageAmount) override;

protected:
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Fire(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float MaxHealth = 100.f;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	FName SocketName;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* BotMesh;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* FireAction;

private:

	FName GetSocketName(bool IsLeft);

	UPROPERTY(EditAnywhere, Category = "Combat")
	float TraceDistance = 5000.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FVector TraceEndLocation;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<ABlasterBeam> BlasterBeam;

	UPROPERTY(EditAnywhere, Category = "Combat")
	bool IsLeftRifle = true;

	UPROPERTY(EditAnywhere, Category = "VFX")
	UNiagaraSystem* BeamBurst;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* FireSound;

};
