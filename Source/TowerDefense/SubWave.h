#pragma once

#include "EnemySpawner.h"
#include "EnemyTypes.h"
#include "SubWave.generated.h"

USTRUCT()
struct FSubWave
{
	GENERATED_USTRUCT_BODY()

private:
	AEnemySpawner* spawner;
	float startTime;
	float nextSpawnTime;
	bool hasStarted;
	bool isFinished;
	int spawnIndex;
	int roundIndex;
	int index;
	
public:
	FSubWave();

	void Start(int ind, float time, AEnemySpawner* _spawner);

	bool Tick(float time);
	
	UPROPERTY(EditAnywhere)
	EnemyType enemyType = EnemyType::Default;

	UPROPERTY(EditAnywhere)
	float startDelay = 0;

	UPROPERTY(EditAnywhere)
	float roundDelay = 0;
	
	UPROPERTY(EditAnywhere)
	float spawnDelay = 1;

	UPROPERTY(EditAnywhere)
	int numEnemies = 5;

	UPROPERTY(EditAnywhere)
	int rounds = 1;
};
