#include "Wave.h"

FWave::FWave()
{
	startTime = -1;
}

void FWave::Start(int index, float time, AEnemySpawner* _spawner)
{
	this->waveIndex = index;
	spawner = _spawner;
	currentTime = time;
	
	subwaveIndex = 0;
	startTime = time + startDelay;
}

bool FWave::Tick(float time)
{
	if (isFinished)
		return true;
	
	currentTime = time;
	if (!hasStarted && time > startTime)
	{
		hasStarted = true;
		SubWaves[0].Start(0, time, spawner);
	}
	
	for (int i = subwaveIndex; i < SubWaves.Num(); i++)
	{
		if (SubWaves[i].Tick(time))
		{
			subwaveIndex++;
			if (subwaveIndex == SubWaves.Num())
			{
				isFinished = true;
				return true;
			}
			SubWaves[subwaveIndex].Start(subwaveIndex, time, spawner);
		}
	}

	return false;
}

void FWave::OnEndSubwave(int index)
{
	subwaveIndex = index + 1;
	
	if (subwaveIndex >= SubWaves.Num())
	{
		isFinished = true;
		return;
	}
	SubWaves[subwaveIndex].Start(index, currentTime, spawner);
}

