// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabbableObjectComponentCPP.h"

// Sets default values for this component's properties
UGrabbableObjectComponentCPP::UGrabbableObjectComponentCPP()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabbableObjectComponentCPP::BeginPlay()
{
	Super::BeginPlay();

	DefaultTransform = GetOwner()->GetActorTransform();
	
}


// Called every frame
void UGrabbableObjectComponentCPP::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGrabbableObjectComponentCPP::OnGrab()
{
	GetOwner()->SetActorEnableCollision(false);
}

void UGrabbableObjectComponentCPP::OnRelease()
{
	GetOwner()->SetActorEnableCollision(true);
	GetOwner()->SetActorTransform(DefaultTransform);
}
