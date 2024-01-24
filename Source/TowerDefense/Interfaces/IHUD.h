#pragma once
#include "TowerDefense/Enums/UnitCommand.h"
#include "TowerDefense/Enums/HUDPanelType.h"

#include "IHUD.generated.h"

UINTERFACE(MinimalAPI)
class UHUDInterface : public UInterface
{
	GENERATED_BODY()
};

class IHUDInterface : public IInterface
{
	GENERATED_BODY()
	
public:
	virtual UnitCommand CurrentCommand() = 0;
	virtual void SetHUDPanelVisibility(HUDPanelType panelType, bool state) = 0;
};
