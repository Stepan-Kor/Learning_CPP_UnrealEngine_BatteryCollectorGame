// Copyright Epic Games, Inc. All Rights Reserved.

#include "CPPLearningGameMode.h"
#include "CPPLearningCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACPPLearningGameMode::ACPPLearningGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
