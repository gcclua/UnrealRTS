#include "HUDPanelBuildings.h"

#include "TowerDefense/Entities/Buildings/BuildingBase.h"

void UHUDPanelBuildingsBase::PopulateData(TScriptInterface<IBuilding> building)
{
	TWeakObjectPtr<ABuildingBase> buildingBase = Cast<ABuildingBase>(building.GetObject());
	if (buildingBase.IsValid())
	{
		bool isConstruction = buildingBase->IsConstruction;
	}
}
