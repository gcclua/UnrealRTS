// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawner.h"
#include "TowerDefense/Entities/Enemies/EnemyBase.h"

AEnemySpawner::AEnemySpawner()
{

}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	for (auto prefab : EnemyPrefabs)
	{
		auto type = prefab.Type;
		auto value = prefab.Blueprint;
		enemyPrefabMap.Add(type, value);
	}
}

AActor* AEnemySpawner::GetSpawn(int index, int& innerIndex)
{
	if (index >= EnemySpawns.Num())
		return nullptr;

	if (EnemySpawns[index].Points.Num() == 0)
		return nullptr;
	
	TArray<AActor*> row = EnemySpawns[index].Points;
	const int rowLen = row.Num();

	if (KeepOnStraightLine)
	{
		if (index == 0)
			innerIndex = FMath::RandRange(0, rowLen - 1);
		if (innerIndex < rowLen)
			return row[innerIndex];
	}
	
	// pick a row either in front or to the left/right by 1
	if (index == 0)
		innerIndex = FMath::RandRange(0, rowLen - 1);
	else
	{
		const bool coinFlip = FMath::RandBool();

		// on the left side
		if (innerIndex == 0)
		{
			if (rowLen > 1 && coinFlip)
				innerIndex = 1;
		}
		else if (innerIndex >= rowLen - 1) // at the far right or further
		{
			if (coinFlip)
				innerIndex--;
		}
		else
		{
			if (coinFlip)
			{
				if (FMath::RandBool())
					innerIndex++;
				else
					innerIndex--;
			}
		}
	}

	if (innerIndex < 0)
		innerIndex = 0;
	else if (innerIndex >= rowLen)
		innerIndex = rowLen - 1;

	return row[innerIndex];
}

void AEnemySpawner::SpawnEnemy(EnemyType enemyType)
{
	if (!enemyPrefabMap.Contains(enemyType))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn due to no prefab found"));
		return;
	}
	
	int innerIndex = 0;
	const AActor* spawn = GetSpawn(0, innerIndex);
	
	if (spawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn due to no spawns found"));
		return;
	}
	
	const TSubclassOf<AEnemyBase> type = enemyPrefabMap[enemyType].Enemy;
	const FVector spawnPos = spawn->GetActorLocation();
	const FRotator spawnRotation = spawn->GetActorRotation();
	const FActorSpawnParameters spawnParams;

	AActor* enemyActor = GetWorld()->SpawnActor<AActor>(type, spawnPos, spawnRotation, spawnParams);
	AEnemyBase* enemy = Cast<AEnemyBase>(enemyActor);
	if (enemy != nullptr)
		enemy->OnSpawn(this, innerIndex);
	else
		UE_LOG(LogTemp, Warning, TEXT("[EnemySpawner] Enemy is null for some reason"));
}
