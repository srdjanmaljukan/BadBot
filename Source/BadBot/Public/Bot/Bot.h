// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Damageable.h"
#include "Bot.generated.h"

class ABlasterBeam;
class UNiagaraSystem;
class USoundBase;

UCLASS()
class BADBOT_API ABot : public AActor, public IDamageable
{
	GENERATED_BODY()
	
public:	
	ABot();

	virtual void Tick(float DeltaTime) override;

	virtual void GetHurt_Implementation(float DamageAmount) override;

protected:
	virtual void BeginPlay() override;

	FTimerHandle TimerHandle;

	void FireBlasterBeam();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components");
	UStaticMeshComponent* BotMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	APawn* TargetPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float BlasterTime = .2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool IsLeftRifle = true;

private:	

	FName GetSocketName(bool IsLeft);

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<ABlasterBeam> BlasterBeam;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UNiagaraSystem* FireExplosion;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* ExplosionSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UNiagaraSystem* BeamBurst;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float InterpSpeed = 8.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float Speed = 100.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float Health = 100.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float MaxHealth = 100.f;
};
