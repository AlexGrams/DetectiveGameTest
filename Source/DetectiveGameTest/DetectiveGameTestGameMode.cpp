// Copyright Epic Games, Inc. All Rights Reserved.

#include "DetectiveGameTestGameMode.h"
#include "DetectiveGameTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADetectiveGameTestGameMode::ADetectiveGameTestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
