#pragma once

//#include "IHUD.h"
#include "IHUDPanelBaseInterface.generated.h"

UINTERFACE(MinimalAPI)
class UHUDPanelBaseInterface : public UInterface
{
	GENERATED_BODY()
};

class IHUDPanelBaseInterface : public IInterface
{
	GENERATED_BODY()
	
public:
	//virtual void Setup(TScriptInterface<IHUDInterface> _hud) = 0;
};
