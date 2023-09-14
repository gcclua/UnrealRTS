// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawner.h"

#include "TowerDefense/Entities/Enemies/EnemyBase.h"

AEnemySpawner::AEnemySpawner()
{
	for (auto prefab : EnemyPrefabs)
	{
		auto type = prefab.Type;
		auto value = prefab.Blueprint;
		enemyPrefabMap.Add(type, value);
	}
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
}

AActor* AEnemySpawner::GetSpawn(int index, int& innerIndex)
{
	if (EnemySpawns.Num() > index || EnemySpawns[index].Points.Num() == 0)
		return nullptr;
	
	const TArray<AActor*> row = EnemySpawns[index].Points;
	innerIndex = FMath::RandRange(0, row.Num() - 1);

	return row[innerIndex];
}

void AEnemySpawner::SpawnEnemy(EnemyType enemyType)
{
	if (!enemyPrefabMap.Contains(enemyType))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn %s due to no prefab found"), enemyType);
		return;
	}

	int innerIndex = 0;
	const AActor* spawn = GetSpawn(0, innerIndex);
	if (spawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn %s due to no spawns found"), enemyType);
		return;
	}

	const TSubclassOf<AEnemyBase> type = enemyPrefabMap[enemyType].Enemy;
	const FVector spawnPos = spawn->GetActorLocation();
	const FRotator spawnRotation = spawn->GetActorRotation();
	const FActorSpawnParameters spawnParams;
	
	AEnemyBase* enemy = GetWorld()->SpawnActor<AEnemyBase>(type, spawnPos, spawnRotation, spawnParams);
	enemy->OnSpawn(this, innerIndex);
}

bool AEnemySpawner::GetNextSpawn(AActor* spawn, int index, int& innerIndex)
{
	if (index >= EnemySpawns.Num())
		return false;

	spawn = GetSpawn(index, innerIndex);
	return true;
}




