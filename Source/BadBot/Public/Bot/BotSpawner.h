// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BotSpawner.generated.h"

class UBoxComponent;
class ATargetPoint;
class ABot;

UCLASS()
class BADBOT_API ABotSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ABotSpawner();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:	

	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TArray<ATargetPoint*> SpawnPoints;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<ABot> BotClass;
	
};
