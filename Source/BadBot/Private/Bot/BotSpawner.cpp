// Fill out your copyright notice in the Description page of Project Settings.


#include "Bot/BotSpawner.h"
#include "Components/BoxComponent.h"
#include "Engine/TargetPoint.h"
#include "Bot/Bot.h"

ABotSpawner::ABotSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);

}

void ABotSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABotSpawner::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UWorld* World = GetWorld();

	if (SpawnPoints.Num() > 0 && World && BotClass)
	{
		for (const ATargetPoint* SpawnPoint : SpawnPoints)
		{
			FVector SpawnPointLocation = SpawnPoint->GetActorLocation();
			World->SpawnActor<ABot>(BotClass, SpawnPointLocation, FRotator(0.f, 0.f, 0.f));
		}

		Destroy();
			
	}
}

void ABotSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

