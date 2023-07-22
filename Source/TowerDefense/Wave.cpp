#include "CoreMinimal.h"
#include "Wave.h"

FWave::FWave()
{
	startTime = -1;
}

void FWave::Start(int index, float time, AEnemySpawnerV2* spawner)
{
	this->waveIndex = index;
	this->spawner = spawner;
	subwaveIndex = 0;
	startTime = time + startDelay;
}

void FWave::Tick(float time)
{
	if (isFinished)
		return;
	
	if (!hasStarted && time > startTime)
	{
		hasStarted = true;
		SubWaves[0].Start(0, time, spawner);
	}
	
	for (int i = 0; i < SubWaves.Num(); i++)
	{
		SubWaves[i].Tick(time);    
	}
}

void FWave::OnEndSubwave(int index)
{
	subwaveIndex = index + 1;
	if (subwaveIndex >= SubWaves.Num())
	{
		spawner->OnEndWave(waveIndex);
		return;
	}
	SubWaves[subwaveIndex].Start(index, spawner->GetTime(), spawner);
}

