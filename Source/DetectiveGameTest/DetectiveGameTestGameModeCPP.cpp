// Fill out your copyright notice in the Description page of Project Settings.


#include "DetectiveGameTestGameModeCPP.h"
#include "DetectiveGameTestCharacterCPP.h"
#include "UObject/ConstructorHelpers.h"


ADetectiveGameTestGameModeCPP::ADetectiveGameTestGameModeCPP()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_DetectiveGameTestCharacterCPP"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}