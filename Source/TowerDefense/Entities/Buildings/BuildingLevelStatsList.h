#pragma once

#include "BuildingLevelStatsBase.h"
#include "BuildingLevelStatsList.generated.h"

UCLASS(Blueprintable)
class UBuildingLevelStatsList : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Instanced, Category = "Stats")
	TArray<UBuildingLevelStatsBase*> StatsInstances;
};