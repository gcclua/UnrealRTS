#include "UnitManager.h"

void AUnitManager::Setup(UHUDBase* _hud, UMouseInteractionBase* _mouseInteraction, APlayerController* _playerController)
{
	hud = _hud;
	mouseInteraction = _mouseInteraction;

	_playerController->InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &AUnitManager::OnLeftClickDown);
	_playerController->InputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &AUnitManager::OnLeftClickUp);
}

void AUnitManager::AddCurrentlySelectedUnit(IUnit* _unit)
{
	if (!selectedUnits.Contains(_unit))
		selectedUnits.Add(_unit);
}

void AUnitManager::ClearCurrentlySelectedUnits()
{
	selectedUnits.Empty();
}

void AUnitManager::OnLeftClickDown()
{
	mouseDownTime = FPlatformTime::Seconds();
}

void AUnitManager::OnLeftClickUp()
{
	constexpr double clickDeltaTime = 0.2;
	const double curTime = FPlatformTime::Seconds();

	if (curTime < clickDeltaTime && hud->CurrentCommand != UnitCommand::None)
	{
		// tell selected units to go somewhere
	}
}
