#pragma once

#include "TowerDefense/Entities/Buildings/BuildingLevelStatsBase.h"
#include "ResourceFarmerLevelStats.generated.h"

UCLASS()
class UResourceFarmerLevelStats : public UBuildingLevelStatsBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GenerateTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int GenerateAmount;
};