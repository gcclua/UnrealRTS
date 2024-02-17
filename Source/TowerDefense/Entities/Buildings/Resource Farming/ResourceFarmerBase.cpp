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
		if (playerVitals != nullptr)
			playerVitals->OnGatherResource(ResourceType, generateAmount);
		else
			UE_LOG(LogTemp, Error, TEXT("AResourceFarmerBase: PlayerVitals is null"));
		
		nextFarmTime = time + generateTime;
	}
}

void AResourceFarmerBase::StartFarming()
{
	playerVitals = APlayerVitalsBase::GetInstance();
	state = ResourceFarmerState::Farming;
	nextFarmTime = GetWorld()->GetTimeSeconds() + generateTime;
}

void AResourceFarmerBase::UpgradeToLevel(int _level)
{
	if (_level > LevelStats.Num())
		return;

	level = _level;
	
	const FResourceFarmerLevelStats stat = LevelStats[level - 1];
	generateAmount = stat.GenerateAmount;
	generateTime = stat.GenerateTime;
}

EntityType AResourceFarmerBase::GetEntityType()
{
	return EntityType::ResourceFarmer;
}

int AResourceFarmerBase::MaxLevel()
{
	return LevelStats.Num();
}

int AResourceFarmerBase::NextCostMoney()
{
	if (level >= LevelStats.Num())
		return -1;
	return LevelStats[level].CostMoney;
}
