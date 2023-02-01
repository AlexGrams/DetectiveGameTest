// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrabbableObjectComponentCPP.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DETECTIVEGAMETEST_API UGrabbableObjectComponentCPP : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabbableObjectComponentCPP();

protected:
	FTransform DefaultTransform;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	/* Called when this object is grabbed. */
	void OnGrab();

	/* Called when this object is released. */
	void OnRelease();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
