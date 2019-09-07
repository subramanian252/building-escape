// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/ActorComponent.h"
#include "Engine.h"

#include "opendoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(Fonopenrequest);



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API Uopendoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	Uopendoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	Fonopenrequest openrequest;

	UPROPERTY(BlueprintAssignable)
	Fonopenrequest closerequest;
	

private:

	AActor* owner;

	UPROPERTY(EditAnywhere)
	float triggeramass = 30.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	float totalmasssoverlappingactors();
};
