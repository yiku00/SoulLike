// Copyright Epic Games, Inc. All Rights Reserved.

#include "SoulLikeGameMode.h"
#include "UObject/ConstructorHelpers.h"

ASoulLikeGameMode::ASoulLikeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/Characters/ParagonRevenant/Characters/Revernant_CPP.Revernant_CPP_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	//Set Default Controller Class to our Blueprint Controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Script/Engine.Blueprint'/Game/Player/BP_PlayerController.BP_PlayerController_C'"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}
