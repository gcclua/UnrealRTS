#pragma once

#include "TowerDefense/Entities/Buildings/BuildingLevelStatsBase.h"
#include "ResourceFarmerLevelStats.generated.h"

USTRUCT()
struct FResourceFarmerLevelStats : public FBuildingLevelStatsBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	float GenerateTime;

	UPROPERTY(EditAnywhere)
	int GenerateAmount;
};