// Fill out your copyright notice in the Description page of Project Settings.

#include "WaveManager.h"

AWaveManager::AWaveManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWaveManager::BeginPlay()
{
	Super::BeginPlay();
	StartSpawning();
}

void AWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!hasStarted || isDone)
		return;
	
	for (int i = 0; i < Waves.Num(); i++)
	{
		if (Waves[i].Tick(currentTime))
		{
			waveIndex++;
			if (waveIndex >= Waves.Num())
			{
				isDone = true;
				return;
			}
			Waves[waveIndex].Start(waveIndex, currentTime, EnemySpawner);
		}
	}
	
	currentTime += DeltaTime;
}

void AWaveManager::StartSpawning()
{
	currentTime = 0;
	waveIndex = 0;
	isDone = false;
	hasStarted = true;
	
	if (Waves.Num() > 0)
		Waves[0].Start(0, currentTime, EnemySpawner);
}

