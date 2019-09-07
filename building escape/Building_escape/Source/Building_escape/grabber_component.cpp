// Fill out your copyright notice in the Description page of Project Settings.


#include "grabber_component.h"
#include "Engine.h"
#include "Gameframework/Actor.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
Ugrabber_component::Ugrabber_component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void Ugrabber_component::BeginPlay()
{
	Super::BeginPlay();
		
	checkingphysicshandle();
	
	inputbindings();
}

void Ugrabber_component::inputbindings()
{
	inputcomponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (inputcomponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s found input component"), *GetOwner()->GetName());

		inputcomponent->BindAction("Grab", IE_Pressed, this, &Ugrabber_component::grab);
		inputcomponent->BindAction("Grab", IE_Released, this, &Ugrabber_component::released);
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s missing physics component"), *GetOwner()->GetName());
	}
}

void Ugrabber_component::checkingphysicshandle()
{
	physicshandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (physicshandle)
	{
		//found the handle
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s missing physics component"), *GetOwner()->GetName());
	}
}

void Ugrabber_component::grab()
{
	UE_LOG(LogTemp, Warning, TEXT("grab pressed"));

	auto Hitresult =getthephysicsbodyinreach();

	auto componenttograb = Hitresult.GetComponent();

	auto Actorhit = Hitresult.GetActor();

	if (Actorhit)
	{
		physicshandle->GrabComponent(componenttograb, NAME_None, componenttograb->GetOwner()->GetActorLocation(), true);
	}

}

void Ugrabber_component::released()
{
	UE_LOG(LogTemp, Warning, TEXT("grab released"));
	physicshandle->ReleaseComponent();
}



// Called every frame
void Ugrabber_component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	


	FVector playerposition;
	FRotator playerrotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerposition, playerrotator);

	//UE_LOG(LogTemp, Warning, TEXT("position:%s, rotation:%s"), *playerposition.ToString(), *playerrotator.ToString());



	FVector linetracend = playerposition + playerrotator.Vector() * reach;

	if (physicshandle->GrabbedComponent)
	{
		physicshandle->SetTargetLocation(linetracend);
			
	}

}

const FHitResult Ugrabber_component::getthephysicsbodyinreach()
{

	FVector playerposition;
	FRotator playerrotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerposition, playerrotator);

	//UE_LOG(LogTemp, Warning, TEXT("position:%s, rotation:%s"), *playerposition.ToString(), *playerrotator.ToString());



	FVector linetracend = playerposition + playerrotator.Vector() * reach;

	FHitResult hit;
	FCollisionQueryParams queryparams(FName(TEXT("")), false, GetOwner());


	GetWorld()->LineTraceSingleByObjectType
	(
		OUT hit,
		playerposition,
		linetracend,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		queryparams
	);

	AActor* hitsubject = hit.GetActor();

	if (hitsubject)
	{
		UE_LOG(LogTemp, Warning, TEXT("The subject I hit:%s"), (*hitsubject->GetName()));
	}
	return hit;
}