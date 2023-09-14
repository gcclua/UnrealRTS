// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyPathRow.h"
#include "GameFramework/Actor.h"
#include "../Entities/EnemyStruct.h"
//#include "TowerDefense/Entities/Enemies/EnemyBase.h"
#include "EnemySpawner.generated.h"

struct FWave;
//class AEnemyBase;

UCLASS()
class TOWERDEFENSE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

private:
	TMap<EnemyType, FEnemyContainer> enemyPrefabMap;
	
protected:
	virtual void BeginPlay() override;

	AActor* GetSpawn(int index, int& innerIndex);

public:
	UPROPERTY(EditAnywhere)
	TArray<FEnemyStruct> EnemyPrefabs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEnemyPathRow> EnemySpawns;
	
	// mono
	AEnemySpawner();

	// spawning stuff
	void SpawnEnemy(EnemyType enemyType);

	bool GetNextSpawn(AActor* spawn, int index, int& innerIndex);
};
