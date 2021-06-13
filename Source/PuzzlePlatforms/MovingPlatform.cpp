// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!HasAuthority())
		return;

	auto Location = GetActorLocation();

	Location += FVector(Speed * DeltaSeconds, 0, 0);
	SetActorLocation(Location);
}
