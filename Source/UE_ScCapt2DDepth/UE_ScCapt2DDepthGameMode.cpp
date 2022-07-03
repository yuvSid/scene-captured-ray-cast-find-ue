// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE_ScCapt2DDepthGameMode.h"
#include "UE_ScCapt2DDepthCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE_ScCapt2DDepthGameMode::AUE_ScCapt2DDepthGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	
}
