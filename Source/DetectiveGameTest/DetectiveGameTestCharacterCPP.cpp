// Fill out your copyright notice in the Description page of Project Settings.

#include "DetectiveGameTestCharacterCPP.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GrabbableObjectComponentCPP.h"


void ADetectiveGameTestCharacterCPP::BeginPlay()
{
	Super::BeginPlay();
	DefaultFOV = GetFirstPersonCameraComponent()->FieldOfView;
}

void ADetectiveGameTestCharacterCPP::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind other interaction events
	PlayerInputComponent->BindAction("PrimaryAction", IE_Released, this, &ADetectiveGameTestCharacterCPP::OnPrimaryActionReleased);
	PlayerInputComponent->BindAction("SecondaryAction", IE_Pressed, this, &ADetectiveGameTestCharacterCPP::OnSecondaryAction);

	PlayerInputComponent->BindAxis("Zoom", this, &ADetectiveGameTestCharacterCPP::Zoom);
}

void ADetectiveGameTestCharacterCPP::Tick(float DeltaSeconds)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Tick function working."));
	if (bIsGrabbing)
	{
		LimitGrabbedObjectPanning();
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

		ObjectLookingAt = nullptr;
		if (bHit)
		{
			UActorComponent* FoundComponent = nullptr;
			FoundComponent = OutHit.GetActor()->FindComponentByClass(UGrabbableObjectComponentCPP::StaticClass());
			if (IsValid(FoundComponent))
			{
				ObjectLookingAt = OutHit.GetActor();
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
		GrabbedObject = ObjectLookingAt;
		GrabbedObjectComponent = (UGrabbableObjectComponentCPP*)GrabbedObject->GetComponentByClass(UGrabbableObjectComponentCPP::StaticClass());
		GrabbedObjectComponent->OnGrab();
		bIsGrabbing = true;
		LockCamera = true;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None, 0);
		// TODO: Timeline component to lerp position. Might be best to just do this part in Blueprint.
		GrabbedObjectStartingLocation = GetFirstPersonCameraComponent()->GetComponentLocation() + GetFirstPersonCameraComponent()->GetForwardVector() * GrabRange;
		GrabbedObject->SetActorLocation(GrabbedObjectStartingLocation);
	}
}

void ADetectiveGameTestCharacterCPP::OnPrimaryActionReleased()
{
	if (bIsGrabbing)
	{
		bIsPanning = false;
	}
}

void ADetectiveGameTestCharacterCPP::OnSecondaryAction()
{
	if (bIsGrabbing)
	{
		LockCamera = false;
		bIsGrabbing = false;
		GrabbedObjectComponent->OnRelease();
		GrabbedObject = nullptr;
		GrabbedObjectComponent = nullptr;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking, 0);
		GetFirstPersonCameraComponent()->SetFieldOfView(DefaultFOV);
	}
}

void ADetectiveGameTestCharacterCPP::AddControllerYawInput(float Val)
{
	if (bIsGrabbing)
	{
		if (bIsPanning)
		{
			// Pan object
			FVector Direction = GetFirstPersonCameraComponent()->GetRightVector() * Val * PanSensitivity;
			GrabbedObject->AddActorWorldOffset(Direction);
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
			// Pan object
			FVector Direction = GetFirstPersonCameraComponent()->GetUpVector() * Val * PanSensitivity * -1.0f;
			GrabbedObject->AddActorWorldOffset(Direction);
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

void ADetectiveGameTestCharacterCPP::Zoom(float Val)
{
	float NewFOV = FMath::Clamp(Val * ZoomSensitivity * -1.0f + GetFirstPersonCameraComponent()->FieldOfView, MinFOV, MaxFOV);
	GetFirstPersonCameraComponent()->SetFieldOfView(NewFOV);
}

void ADetectiveGameTestCharacterCPP::LimitGrabbedObjectPanning()
{
	if (!IsValid(GrabbedObject))
	{
		return;
	}

	if (FVector::Distance(GrabbedObject->GetActorLocation(), GrabbedObjectStartingLocation) > GrabRange)
	{
		FVector DirectionFromStart = GrabbedObject->GetActorLocation() - GrabbedObjectStartingLocation;
		DirectionFromStart.Normalize();
		GrabbedObject->SetActorLocation(GrabbedObjectStartingLocation + DirectionFromStart * GrabRange);
	}
}