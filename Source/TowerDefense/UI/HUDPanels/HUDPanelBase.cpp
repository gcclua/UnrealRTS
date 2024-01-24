#include "HUDPanelBase.h"

void UHUDPanelBase::Setup(TScriptInterface<IHUDInterface> _hud)
{
	hud = _hud;
	OnInit();
}

void UHUDPanelBase::OnInit_Implementation()
{

}
