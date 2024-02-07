#pragma once

#include "BuildingLevelStatsBase.generated.h"

UCLASS()
class UBuildingLevelStatsBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CostMoney;
};