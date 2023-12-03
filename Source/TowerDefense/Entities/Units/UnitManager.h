#pragma once
#include "IUnit.h"

#include "UnitManager.generated.h"

UCLASS()
class AUnitManager : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<IUnit*> selectedUnits;
public:
	void AddCurrentlySelectedUnit(IUnit* _unit);
	void ClearCurrentlySelectedUnits();
};
