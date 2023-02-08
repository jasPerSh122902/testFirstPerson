// Fill out your copyright notice in the Description page of Project Settings.


#include "TraceComponent.h"

// Sets default values for this component's properties
UTraceComponent::UTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UTraceComponent::DoTrace(FVector location, FRotator rotation, UWorld* currentWorld)
{
}

// Called every frame
void UTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTraceComponent::GetTraceBullet(float multiplyLength, FColor color, bool linePresist, float lifeTime, int proity, float thickness, UWorld* currentWorld, FVector location, FVector endLocation, FRotator rotation)
{
}

