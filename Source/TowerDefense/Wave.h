#pragma once

#include "SubWave.h"
#include "CoreMinimal.h"
#include "Wave.generated.h"

USTRUCT()
struct FWave
{
	GENERATED_USTRUCT_BODY()

private:
	UPROPERTY() AEnemySpawner* spawner;
	float startTime;
	bool hasStarted;
	bool isFinished;
	int subwaveIndex;
	int waveIndex;
	float currentTime;
	
public:
	FWave();

	void Start(int index, float time, AEnemySpawner* _spawner);
	
	bool Tick(float time);

	void OnEndSubwave(int index);

	UPROPERTY(EditAnywhere)
	float startDelay = 0;
	
	UPROPERTY(EditAnywhere)
	TArray<FSubWave> SubWaves;
};
