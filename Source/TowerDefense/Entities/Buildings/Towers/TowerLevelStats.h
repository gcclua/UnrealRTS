#pragma once

#include "TowerDefense/Entities/Buildings/BuildingLevelStatsBase.h"
#include "TowerLevelStats.generated.h"

UCLASS()
class UTowerLevelStats : public UBuildingLevelStatsBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;
};