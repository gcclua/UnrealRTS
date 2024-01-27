// Fill out your copyright notice in the Description page of Project Settings.

#include "ResourceFarmerBase.h"
#include "TowerDefense/Utils/Logger.h"

AResourceFarmerBase::AResourceFarmerBase()
{
	state = ResourceFarmerState::Idle;
	PrimaryActorTick.bCanEverTick = true;
}

void AResourceFarmerBase::BeginPlay()
{
	Super::BeginPlay();
}

void AResourceFarmerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (state != ResourceFarmerState::Farming)
		return;

	const double time = GetWorld()->GetTimeSeconds();
	if (time >= nextFarmTime)
	{
		playerVitals->OnGatherResource(ResourceType, 1);
		nextFarmTime = time + GenerateTime;
	}
}

void AResourceFarmerBase::StartFarming()
{
	playerVitals = Cast<APlayerVitalsBase>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerVitalsBase::StaticClass()));
	state = ResourceFarmerState::Farming;
	nextFarmTime = GetWorld()->GetTimeSeconds() + GenerateTime;
}

EntityType AResourceFarmerBase::GetEntityType()
{
	return EntityType::ResourceFarmer;
}
