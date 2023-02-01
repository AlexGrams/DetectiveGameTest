// Fill out your copyright notice in the Description page of Project Settings.

#include "DetectiveGameTestCharacterCPP.h"
#include "Camera/CameraComponent.h"

void ADetectiveGameTestCharacterCPP::Tick(float DeltaSeconds)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Tick function working."));
	if (IsGrabbing)
	{

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
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Looking at an object within range."));
			UActorComponent* FoundComponent = nullptr;
			FoundComponent = OutHit.GetActor()->FindComponentByClass(GrabbableObjectClass);
			if (IsValid(FoundComponent))
			{
				ObjectLookingAt = OutHit.GetActor();
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Can be grabbed."));
			}
		}
	}
}