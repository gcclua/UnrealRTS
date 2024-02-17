#pragma once

#include "TowerDefense/Entities/Buildings/BuildingLevelStatsBase.h"
#include "TowerLevelStats.generated.h"

USTRUCT()
struct FTowerLevelStats : public FBuildingLevelStatsBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	float FireRate;

	UPROPERTY(EditAnywhere)
	float Damage;

	UPROPERTY(EditAnywhere)
	float Range;
};