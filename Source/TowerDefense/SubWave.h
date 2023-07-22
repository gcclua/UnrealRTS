#pragma once

//#include "EnemySpawnerV2.h"
#include "EnemyTypes.h"
#include "SubWave.generated.h"

//class AEnemySpawnerV2;

USTRUCT()
struct FSubWave
{
	GENERATED_USTRUCT_BODY()

private:
	//UPROPERTY() AEnemySpawnerV2* spawner;
	float startTime;
	float nextSpawnTime;
	bool hasStarted;
	bool isFinished;
	int spawnIndex;
	int roundIndex;
	int index;
	
public:
	FSubWave();

	void Start(int index, float time/*, AEnemySpawnerV2* spawner*/);

	bool Tick(float time);

	float GetTotalTime();
	
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
