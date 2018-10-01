// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool MissionSuccess)
{
	if (InstigatorPawn)
	{
		UGameplayStatics::PlaySound2D(this, EndGameSound);
		InstigatorPawn->DisableInput(nullptr);

		if (ViewpointClass != nullptr)
		{

			TArray<AActor*> ReturnedActors;

			UGameplayStatics::GetAllActorsOfClass(this, ViewpointClass, ReturnedActors);


			if (ReturnedActors.Num() > 0)
			{
				AActor* VP = ReturnedActors[0];

				APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());

				if (PC)
				{
					PC->SetViewTargetWithBlend(VP, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}

			}
		}

		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Viewpoint Class in null , please update."))
		}

		

	}

	OnMissionComplete(InstigatorPawn, MissionSuccess);
}
