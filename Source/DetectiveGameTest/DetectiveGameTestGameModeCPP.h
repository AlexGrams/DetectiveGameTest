// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DetectiveGameTestGameModeCPP.generated.h"

/**
 * Custom GameMode which sets the Default Pawn Class to the one with equivalent C++ functionality.
 */
UCLASS()
class DETECTIVEGAMETEST_API ADetectiveGameTestGameModeCPP : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADetectiveGameTestGameModeCPP();
	
};
