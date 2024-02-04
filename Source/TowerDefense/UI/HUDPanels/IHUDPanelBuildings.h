#pragma once

#include "TowerDefense/Entities/Buildings/IBuilding.h"
#include "IHUDPanelBuildings.generated.h"

UINTERFACE(MinimalAPI)
class UHUDPanelBuildingsInterface : public UInterface
{
	GENERATED_BODY()
};

class IHUDPanelBuildingsInterface : public IInterface
{
	GENERATED_BODY()
	
public:
	virtual void PopulateData(TScriptInterface<IBuilding> building) = 0;
};
