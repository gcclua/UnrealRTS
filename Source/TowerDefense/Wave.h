#pragma once

#include "SubWave.h"
#include "EnemySpawnerV2.h"
#include "Wave.generated.h"

class AEnemySpawnerV2;
struct FSubwave;

USTRUCT()
struct FWave
{
	GENERATED_USTRUCT_BODY()

private:
	UPROPERTY() AEnemySpawnerV2* spawner;
	float startTime;
	bool hasStarted;
	bool isFinished;
	int subwaveIndex;
	int waveIndex;
	
public:
	FWave();

	void Start(int index, float time, AEnemySpawnerV2* spawner);
	
	void Tick(float time);

	void OnEndSubwave(int index);

	UPROPERTY(EditAnywhere)
	float startDelay = 0;
	
	UPROPERTY(EditAnywhere)
	TArray<FSubWave> SubWaves;
};
