#pragma once

#include "EnemyContainer.h"
#include "../Enums/EnemyTypes.h"
//#include "TowerDefense/Entities/Enemies/EnemyBase.h"
#include "EnemyStruct.generated.h"

struct FEnemyContainer;
//class AEnemySpawner;
//class AEnemyBase;

USTRUCT()
struct FEnemyStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	EnemyType Type;

	UPROPERTY(EditAnywhere)
	FEnemyContainer Blueprint;
};
