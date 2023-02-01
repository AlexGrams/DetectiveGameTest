// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DetectiveGameTestCharacter.h"
#include "DetectiveGameTestCharacterCPP.generated.h"

/**
 * 
 */
UCLASS()
class DETECTIVEGAMETEST_API ADetectiveGameTestCharacterCPP : public ADetectiveGameTestCharacter
{
	GENERATED_BODY()
	
protected:
	/* Lowest FOV for zooming. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction")
	float MinFOV;

	/* How far the player can interact with objects. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction")
	float GrabRange;

	/* Physics Object Type of objects that can be interacted with. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction")
	TArray<TEnumAsByte<EObjectTypeQuery>> GrabbableObjectTypes;

	/* TEMP: Component class of grabbable objects. Replace with actual C++ class once implemented.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction")
	TSubclassOf<UActorComponent> GrabbableObjectClass;

	/* Base camera FOV setting for when the player is walking around. */
	float DefaultFOV;

	/* True when player is interacting with an object. */
	bool IsGrabbing;

	/* Which grabbable object (if any) the player is currently looking at. */
	AActor* ObjectLookingAt;

	virtual void Tick(float DeltaSeconds) override;
};
