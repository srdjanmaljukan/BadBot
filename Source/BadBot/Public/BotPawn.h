// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "BotPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UFloatingPawnMovement;
class UInputMappingContext;
class UInputAction;

UCLASS()
class BADBOT_API ABotPawn : public APawn
{
	GENERATED_BODY()

public:
	ABotPawn();

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Fire(const FInputActionValue& Value);

	void FireRifle(bool IsLeftRifle);
	FTransform TraceForSpawnTranform(bool IsLeftRifle);
	FVector RifleTrace();
	FTransform GetSpawnTransform(FVector TraceEnd, bool IsLeftRifle);

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	float Health = 100.f;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	FName SocketName;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UStaticMeshComponent* BotMesh;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;

private:

};
