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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction")
	float RotationSensitivity = 1.0f;

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
	bool bIsGrabbing;

	/* True when player holds down the interact input while grabbing an object. */
	bool bIsPanning;

	/* Which grabbable object (if any) the player is currently looking at. */
	AActor* ObjectLookingAt = nullptr;

	/* Object player is currently interacting with. */
	AActor* GrabbedObject = nullptr;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	/* Input started. Interact with an object or start panning. */
	virtual void OnPrimaryAction() override;

public:
	/**
	 * Allows locking rotation and interacting with a grabbed object along mouse X axis.
	 * @param Val Amount to add to Yaw. This value is multiplied by the PlayerController's InputYawScale value.
	 * @see PlayerController::InputYawScale
	 */
	virtual void AddControllerYawInput(float Val) override;

	/**
	 * Allows locking rotation and interacting with a grabbed object along mouse Y axis.
	 * @param Val Amount to add to Pitch. This value is multiplied by the PlayerController's InputPitchScale value.
	 * @see PlayerController::InputPitchScale
	 */
	virtual void AddControllerPitchInput(float Val) override;
};
