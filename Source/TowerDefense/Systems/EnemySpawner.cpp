// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawner.h"

AEnemySpawner::AEnemySpawner()
{

}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemySpawner::SpawnEnemy(EnemyType enemyType)
{
	for (int i = 0; i < EnemyPrefabs.Num(); i++)
	{
		if (EnemyPrefabs[i].Type == enemyType)
		{
			const FTransform trans = GetActorTransform();
			const TSubclassOf<AActor> type = EnemyPrefabs[i].Blueprint;

			const FActorSpawnParameters spawnParams;
			GetWorld()->SpawnActor<AActor>(type, trans.GetLocation(), trans.GetRotation().Rotator(), spawnParams);

			break;
		}
	}
}


