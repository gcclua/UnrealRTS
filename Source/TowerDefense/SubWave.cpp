#include "SubWave.h"

FSubWave::FSubWave()
{
	hasStarted = false;
	isFinished = false;
	startTime = -1;
	nextSpawnTime = -1;
	spawnIndex = 0;
	roundIndex = 0;
	index = -1;
}

void FSubWave::Start(int index, float time/*, AEnemySpawnerV2* spawner*/)
{
	this->index = index;
	//this->spawner = spawner;
	
	startTime = time;
	hasStarted = true;
	isFinished = false;
	nextSpawnTime = startDelay + spawnDelay;
}

bool FSubWave::Tick(float time)
{
	if (!hasStarted || isFinished)
		return false;
	
	const float normalisedTime = time - startTime;
	
	if (normalisedTime >= nextSpawnTime)
	{
		//spawner->SpawnEnemy(enemyType);

		spawnIndex++;
		
		if (spawnIndex >= numEnemies)
		{
			roundIndex++;
			if (roundIndex >= rounds)
			{
				isFinished = true;
				return true;
			}
			else
			{
				spawnIndex = 0;
				nextSpawnTime = normalisedTime + roundDelay;
			}
		}
		else
		{
			nextSpawnTime = normalisedTime + spawnDelay;
		}
	}

	return false;
}

