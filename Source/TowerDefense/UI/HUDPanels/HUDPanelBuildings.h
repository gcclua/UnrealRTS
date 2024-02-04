#pragma once

#include "HUDPanelBase.h"
#include "IHUDPanelBuildings.h"
#include "HUDPanelBuildings.generated.h"

UCLASS(ABSTRACT)
class UHUDPanelBuildingsBase : public UHUDPanelBase, public IHUDPanelBuildingsInterface
{
	GENERATED_BODY()
	
public:
	
	virtual void PopulateData(TScriptInterface<IBuilding> building) override;
};
