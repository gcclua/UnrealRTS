// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wave.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyStruct.h"
#include "EnemySpawnerV2.generated.h"

struct FWave;

UCLASS()
class TOWERDEFENSE_API AEnemySpawnerV2 : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	// properties
	UPROPERTY(EditAnywhere)
	TArray<FWave> Waves;

	UPROPERTY(EditAnywhere)
	TArray<FEnemyStruct> EnemyPrefabs;

	// mono
	AEnemySpawnerV2();
	virtual void Tick(float DeltaTime) override;
	
	// wave stuff
	void StartSpawning();
	float GetTime() const;
	void OnEndWave(int index);

	// spawning stuff
	void SpawnEnemy(EnemyType enemyType);

private:
	float currentTime;
	bool hasStarted;
};
