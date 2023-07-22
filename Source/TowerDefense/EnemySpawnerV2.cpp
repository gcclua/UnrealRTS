// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawnerV2.h"

AEnemySpawnerV2::AEnemySpawnerV2()
{
	PrimaryActorTick.bCanEverTick = true; // tell this to tick every frame
}

void AEnemySpawnerV2::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemySpawnerV2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!hasStarted)
		return;
	
    for (int i = 0; i < Waves.Num(); i++)
    {
		Waves[i].Tick(currentTime);    
    }
	
	currentTime += DeltaTime;
}

void AEnemySpawnerV2::StartSpawning()
{
	currentTime = 0;
	//if (Waves.Num() > 0)
		//Waves[0].Start(0, currentTime, *this);
}

float AEnemySpawnerV2::GetTime() const
{
	return currentTime;
}

void AEnemySpawnerV2::OnEndWave(int index)
{
	
}

void AEnemySpawnerV2::SpawnEnemy(EnemyType enemyType)
{
	for (int i = 0; i < EnemyPrefabs.Num(); i++)
	{
		if (EnemyPrefabs[i].Type == enemyType)
		{
			const FTransform trans = GetActorTransform();
			TSubclassOf<AActor> type = EnemyPrefabs[i].Blueprint;

			FActorSpawnParameters spawnParams;
			GetWorld()->SpawnActor<AActor>(type, trans.GetLocation(), trans.GetRotation().Rotator(), spawnParams);

			break;
		}
	}
}


