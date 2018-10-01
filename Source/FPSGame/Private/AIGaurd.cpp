// Fill out your copyright notice in the Description page of Project Settings.

#include "AIGaurd.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "FPSGameMode.h"
#include "Engine/World.h"


// Sets default values
AAIGaurd::AAIGaurd()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AAIGaurd::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AAIGaurd::OnHearSound);

}

// Called when the game starts or when spawned
void AAIGaurd::BeginPlay()
{
	Super::BeginPlay();
	
	ORotation = GetActorRotation();
}

void AAIGaurd::OnPawnSeen(APawn * SeenPawn)
{
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);

	AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());

	if (GM)
	{
		GM->CompleteMission(SeenPawn, false);
	}
}

void AAIGaurd::OnHearSound(APawn * InstigatorPawn, const FVector & Location, float Volume)
{
	
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Black, false, 10.0f);

	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	FRotator LookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	LookAt.Pitch = 0.0f;
	LookAt.Roll = 0.0f;

	SetActorRotation(LookAt);

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AAIGaurd::ResetOrientation, 3.0f);
}

void AAIGaurd::ResetOrientation()
{
	SetActorRotation(ORotation);
}

// Called every frame
void AAIGaurd::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIGaurd::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

