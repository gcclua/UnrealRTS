#pragma once

#include "EnemyTypes.h"
#include "SubWave.generated.h"

USTRUCT()
struct FSubWave
{
	GENERATED_USTRUCT_BODY()
	
public:
	FSubWave();

	UPROPERTY(EditAnywhere)
	EnemyType enemyType = EnemyType::Default;

	UPROPERTY(EditAnywhere)
	float startDelay = 0;

	UPROPERTY(EditAnywhere)
	float spawnDelay = 1;

	UPROPERTY(EditAnywhere)
	int numEnemies = 5;

	UPROPERTY(EditAnywhere)
	int rounds = 1;
};
