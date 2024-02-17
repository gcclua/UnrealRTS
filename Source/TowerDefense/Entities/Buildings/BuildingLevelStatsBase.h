#pragma once

#include "BuildingLevelStatsBase.generated.h"

USTRUCT()
struct FBuildingLevelStatsBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	int Level;

	UPROPERTY(EditAnywhere)
	int CostMoney;
};