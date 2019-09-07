// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Components/ActorComponent.h"
#include "Engine.h"
#include "grabber_component.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API Ugrabber_component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	Ugrabber_component();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void inputbindings();

	void checkingphysicshandle();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	float reach = 100.f;

	UPhysicsHandleComponent* physicshandle = nullptr ;

	UInputComponent* inputcomponent = nullptr;
	 
	void grab ();

	void released();

	const FHitResult getthephysicsbodyinreach();

};
