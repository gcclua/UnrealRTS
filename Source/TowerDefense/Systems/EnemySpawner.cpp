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
		//UE_LOG(LogTemp, Warning, TEXT("Add: %d"), static_cast<int>(prefab.Type));

		
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
	innerIndex = FMath::RandRange(0, row.Num() - 1);

	if (index != 0)
		UE_LOG(LogTemp, Warning, TEXT("GetSpawn: %d: %d"), index, innerIndex);
	

	return row[innerIndex];
}

void AEnemySpawner::Fuck()
{
	UE_LOG(LogTemp, Warning, TEXT("Fuck"));
}


void AEnemySpawner::SpawnEnemy(EnemyType enemyType)
{
	//UE_LOG(LogTemp, Warning, TEXT("Spawn: %d"), static_cast<int>(enemyType));

	if (!enemyPrefabMap.Contains(enemyType))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn due to no prefab found"));
		return;
	}
	
	int innerIndex = 0;
	AActor* spawn = GetSpawn(0, innerIndex);
	
	if (spawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn due to no spawns found"));
		return;
	}
	
	const TSubclassOf<AEnemyBase> type = enemyPrefabMap[enemyType].Enemy;
	const FVector spawnPos = spawn->GetActorLocation();
	const FRotator spawnRotation = spawn->GetActorRotation();
	const FActorSpawnParameters spawnParams;
	
	UE_LOG(LogTemp, Warning, TEXT("Spawning %s"), *type->GetName());
	
	AActor* enemyActor = GetWorld()->SpawnActor<AActor>(type, spawnPos, spawnRotation, spawnParams);
	AEnemyBase* enemy = Cast<AEnemyBase>(enemyActor);
	enemy->OnSpawn(this, innerIndex);
}
