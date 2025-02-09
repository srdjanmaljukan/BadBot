// Fill out your copyright notice in the Description page of Project Settings.


#include "Bot/Bot.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "BlasterBeam/BlasterBeam.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Sound/SoundBase.h"

ABot::ABot()
{
	PrimaryActorTick.bCanEverTick = true;

	BotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BotMesh"));
	SetRootComponent(BotMesh);

}

void ABot::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (!World) return;

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(World, APawn::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
	{
		TargetPawn = Cast<APawn>(FoundActors[0]);
	}

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABot::FireBlasterBeam, BlasterTime, true);

	// TODO: Clear timer when actor is destroyed
	
}

void ABot::FireBlasterBeam()
{
	UWorld* World = GetWorld();

	if (TargetPawn && World)
	{
	    FName SocketName = GetSocketName(IsLeftRifle);
	    FTransform SocketTransform = BotMesh->GetSocketTransform(SocketName);
	    FVector SocketLocation = SocketTransform.GetLocation();
		FRotator SocketRotation = SocketTransform.GetRotation().Rotator();
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(SocketLocation, TargetPawn->GetActorLocation());
		FTransform SpawnTransform = FTransform(LookAtRotation, SocketLocation);

		if (BlasterBeam && BeamBurst && FireSound)
		{
			World->SpawnActor<ABlasterBeam>(BlasterBeam, SocketTransform);
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, BeamBurst, SocketLocation, SocketRotation);
			UGameplayStatics::PlaySoundAtLocation(World, FireSound, SocketLocation);
		}

	    IsLeftRifle = !IsLeftRifle;
	}
}

FName ABot::GetSocketName(bool IsLeft)
{
	if (IsLeft)
	{
		return FName("Rifle_L");
	}
	else
	{
		return FName("Rifle_R");
	}
}

void ABot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetPawn)
	{
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPawn->GetActorLocation());
		FRotator InterpRotation = UKismetMathLibrary::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, InterpSpeed);
		SetActorRotation(InterpRotation);
		AddActorWorldOffset(GetActorForwardVector() * Speed * DeltaTime);
	}

}

void ABot::GetHurt_Implementation(float DamageAmount)
{
	Health = FMath::Clamp(Health - DamageAmount, 0.f, MaxHealth);
	if (Health <= 0.f)
	{
		UWorld* World = GetWorld();
		if (World && FireExplosion && ExplosionSound)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, FireExplosion, GetActorLocation());
			UGameplayStatics::PlaySoundAtLocation(World, ExplosionSound, GetActorLocation());
		}
		Destroy();
	}
}

