#include "UnitManager.h"

void AUnitManager::AddCurrentlySelectedUnit(IUnit* _unit)
{
	if (!selectedUnits.Contains(_unit))
		selectedUnits.Add(_unit);
}

void AUnitManager::ClearCurrentlySelectedUnits()
{
	selectedUnits.Empty();
}
