// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIGaurd.generated.h"

class UPawnSensingComponent;

UCLASS()
class FPSGAME_API AAIGaurd : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIGaurd();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION(BlueprintCallable, Category = "Function")
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION(BlueprintCallable, Category = "Function")
	void OnHearSound(APawn* InstigatorPawn, const FVector& Location, float Volume);

	FRotator ORotation;


	UFUNCTION(BlueprintCallable, Category = "Function")
	void ResetOrientation();

	FTimerHandle TimerHandle_ResetOrientation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
