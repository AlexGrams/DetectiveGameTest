// Fill out your copyright notice in the Description page of Project Settings.

#include "DetectiveGameTestCharacterCPP.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


void ADetectiveGameTestCharacterCPP::BeginPlay()
{
	Super::BeginPlay();
	DefaultFOV = GetFirstPersonCameraComponent()->FieldOfView;
}

void ADetectiveGameTestCharacterCPP::Tick(float DeltaSeconds)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Tick function working."));
	if (bIsGrabbing)
	{
		// TODO: Zoom in/out
	}
	else
	{
		// Check if the playing is looking at something that can be grabbed.
		FHitResult OutHit;
		FVector Start = GetFirstPersonCameraComponent()->GetComponentLocation();
		FVector End = Start + GetFirstPersonCameraComponent()->GetForwardVector() * GrabRange; 
		FCollisionObjectQueryParams ObjectParams = FCollisionObjectQueryParams(GrabbableObjectTypes);
		FCollisionQueryParams Params = FCollisionQueryParams();

		bool bHit = GetWorld()->LineTraceSingleByObjectType(OutHit, Start, End, ObjectParams, Params);

		if (bHit)
		{
			UActorComponent* FoundComponent = nullptr;
			FoundComponent = OutHit.GetActor()->FindComponentByClass(GrabbableObjectClass);
			if (IsValid(FoundComponent))
			{
				ObjectLookingAt = OutHit.GetActor();
			}
			else
			{
				ObjectLookingAt = nullptr;
			}
		}
	}
}

void ADetectiveGameTestCharacterCPP::OnPrimaryAction()
{
	if (bIsGrabbing)
	{
		bIsPanning = true;
	}
	// Check if the player is looking at something that can be grabbed. If so, allow them to rotate it.
	else if (IsValid(ObjectLookingAt))
	{
		// TODO: set a GrabbableObjectComponent variable for later use.
		GrabbedObject = ObjectLookingAt;
		bIsGrabbing = true;
		LockCamera = true;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None, 0);
		// TODO: Timeline component to lerp position. Might be best to just do this part in Blueprint.
		FVector ObjectLocation = GetFirstPersonCameraComponent()->GetComponentLocation() + GetFirstPersonCameraComponent()->GetForwardVector() * GrabRange;
		GrabbedObject->SetActorLocation(ObjectLocation);
	}
}

void ADetectiveGameTestCharacterCPP::AddControllerYawInput(float Val)
{
	if (bIsGrabbing)
	{
		if (bIsPanning)
		{
			// TODO: Pan object
		}
		else
		{
			// Rotate object
			FVector Axis = GetFirstPersonCameraComponent()->GetUpVector().GetSafeNormal();
			float FOVScale = DefaultFOV / GetFirstPersonCameraComponent()->FieldOfView;
			float Angle = Val * RotationSensitivity * FOVScale * -1.0f;
			FRotator Rotator = FQuat(Axis, FMath::DegreesToRadians(Angle)).Rotator();
			GrabbedObject->AddActorWorldRotation(Rotator);
		}
	}
	else
	{
		Super::AddControllerYawInput(Val);
	}
}

void ADetectiveGameTestCharacterCPP::AddControllerPitchInput(float Val)
{
	if (bIsGrabbing)
	{
		if (bIsPanning)
		{

		}
		else
		{
			// Rotate object
			FVector Axis = GetFirstPersonCameraComponent()->GetRightVector().GetSafeNormal();
			float FOVScale = DefaultFOV / GetFirstPersonCameraComponent()->FieldOfView;
			float Angle = Val * RotationSensitivity * FOVScale * -1.0f;
			FRotator Rotator = FQuat(Axis, FMath::DegreesToRadians(Angle)).Rotator();
			GrabbedObject->AddActorWorldRotation(Rotator);
		}
	}
	else
	{
		Super::AddControllerPitchInput(Val);
	}
}