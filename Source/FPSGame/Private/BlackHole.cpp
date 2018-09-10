// Fill out your copyright notice in the Description page of Project Settings.

#include "BlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Meshcomp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	Meshcomp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = Meshcomp;

	OuterSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("OutSphereComp"));
	OuterSphereComp->SetSphereRadius(3000);
	OuterSphereComp->SetupAttachment(Meshcomp);

	InnerSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComp"));
	InnerSphereComp->SetSphereRadius(100);
	InnerSphereComp->SetupAttachment(Meshcomp);

	InnerSphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OverlapInnerSphere);

}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABlackHole::OverlapInnerSphere(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> OverlappingComp;
	OuterSphereComp->GetOverlappingComponents(OverlappingComp);

	for (int32 i = 0; i < OverlappingComp.Num(); i++)
	{

		UPrimitiveComponent* PrimComp = OverlappingComp[i];

		if (PrimComp && PrimComp->IsSimulatingPhysics())
		{
			const float SphereRadius = OuterSphereComp->GetScaledSphereRadius();
			const float ForceStrength = -2000;

			PrimComp->AddRadialForce(GetActorLocation(), SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);

		}

	}

}

