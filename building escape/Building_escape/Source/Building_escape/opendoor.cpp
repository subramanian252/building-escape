// Fill out your copyright notice in the Description page of Project Settings.
#include "opendoor.h"

#include "Engine.h"

#include "Gameframework/Actor.h"

#include "Delegates/Delegate.h"




// Sets default values for this component's properties
Uopendoor::Uopendoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	owner = GetOwner();

	// ...
}


// Called when the game starts
void Uopendoor::BeginPlay()
{
	Super::BeginPlay();
}




// Called every frame
void Uopendoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (totalmasssoverlappingactors() > triggeramass)
	{
		openrequest.Broadcast();

	}
	else
	{
		closerequest.Broadcast();
	}
		
	
}

float Uopendoor::totalmasssoverlappingactors()
{
	float totalmass = 0.f;
	TArray<AActor*> overlappingactors;
	PressurePlate->GetOverlappingActors(OUT overlappingactors);

	for (auto& actor : overlappingactors)
	{
		totalmass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();

		UE_LOG(LogTemp, Warning, TEXT("%s onpressureplate "), *actor->GetName());
			
	}
	return totalmass;
}

