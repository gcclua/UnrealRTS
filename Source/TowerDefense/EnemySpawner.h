// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyStruct.h"
#include "EnemySpawner.generated.h"

struct FWave;

UCLASS()
class TOWERDEFENSE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TArray<FEnemyStruct> EnemyPrefabs;

	// mono
	AEnemySpawner();

	// spawning stuff
	void SpawnEnemy(EnemyType enemyType);
};
