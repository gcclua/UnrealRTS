#pragma once

//#include "TowerDefense/Entities/Enemies/EnemyBase.h"
#include "EnemyContainer.generated.h"

class AEnemyBase;

USTRUCT()
struct FEnemyContainer
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemyBase> Enemy;
};
