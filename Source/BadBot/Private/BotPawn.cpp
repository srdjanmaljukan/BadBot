// Fill out your copyright notice in the Description page of Project Settings.


#include "BotPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"

ABotPawn::ABotPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BotMesh"));
	SetRootComponent(BotMesh);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 30.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

void ABotPawn::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void ABotPawn::Move(const FInputActionValue& Value)
{
	const FVector DirectionLocal = Value.Get<FVector>();

	const FRotator Rotation = GetController()->GetControlRotation();
	const FVector Forward = Rotation.Vector();
	const FVector Right = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);
	const FVector Up = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Z);

	FloatingPawnMovement->AddInputVector(Forward * DirectionLocal.X);
	FloatingPawnMovement->AddInputVector(Right * DirectionLocal.Y);
	FloatingPawnMovement->AddInputVector(Up * DirectionLocal.Z);
}

void ABotPawn::Look(const FInputActionValue& Value)
{
	const FVector2D Look = Value.Get<FVector2D>();
	if (GetController())
	{
		AddControllerYawInput(Look.X);
		AddControllerPitchInput(Look.Y);
	}
}

void ABotPawn::Fire(const FInputActionValue& Value)
{
	// Add Flip Flop logic to toggle between firing and not firing
	bool PlaceHolder = false;

	if (Value.Get<bool>())
	{
		FireRifle(PlaceHolder);
	}
}

void ABotPawn::FireRifle(bool IsLeftRifle)
{
	
}

FTransform ABotPawn::TraceForSpawnTranform(bool IsLeftRifle)
{
	const FVector TraceEndLocation = RifleTrace();

	return GetSpawnTransform(TraceEndLocation, IsLeftRifle);
}

FVector ABotPawn::RifleTrace()
{
	return FVector();
}

FTransform ABotPawn::GetSpawnTransform(FVector TraceEnd, bool IsLeftRifle)
{
	return FTransform();
}

void ABotPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABotPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABotPawn::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABotPawn::Look);
}

