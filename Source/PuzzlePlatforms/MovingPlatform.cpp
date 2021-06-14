// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!HasAuthority())
	{
		return;
	}

	auto Location = GetActorLocation();
	const auto JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
	const auto JourneyTraveled = (Location - GlobalStartLocation).Size();

	if (JourneyTraveled > JourneyLength)
	{
		Swap(GlobalStartLocation, GlobalTargetLocation);
	}
	
	const auto Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();

	Location += Direction * (Speed * DeltaSeconds);
	SetActorLocation(Location);
}
