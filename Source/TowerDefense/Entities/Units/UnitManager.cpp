#include "UnitManager.h"

#include "TowerDefense/UI/MouseInteractionBase.h"

AUnitManager::AUnitManager()
{

}

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

void AUnitManager::RemoveCurrentlySelectedUnit(IUnit* _unit)
{
	if (selectedUnits.Contains(_unit))
		selectedUnits.Remove(_unit);
}

void AUnitManager::OnLeftClickDown()
{
	mouseDownTime = FPlatformTime::Seconds();
}

void AUnitManager::OnLeftClickUp()
{
	constexpr double clickDeltaTime = 0.2;
	const double curTime = FPlatformTime::Seconds();

	const float clickTime = curTime - mouseDownTime;
	if (clickTime < clickDeltaTime && hud->CurrentCommand != UnitCommand::None && selectedUnits.Num() > 0)
	{
		// tell selected units to go somewhere
		const FVector location = mouseInteraction->GetMousePosInWorld(true);

		for (IUnit* unit : selectedUnits)
		{
			unit->MoveToLocation(location);
		}

		const float SphereRadius = 10.0f; // Set the radius of the sphere
		const int32 Segments = 12; // Set the number of segments for the sphere
		const FColor SphereColor = FColor::Red; // Set the color of the sphere
		const float LifeTime = -1.0f; // Negative lifetime means the sphere is permanent

		DrawDebugSphere(
			GetWorld(),
			location,
			SphereRadius,
			Segments,
			SphereColor,
			true, // Persistent lines
			LifeTime
		);
	}
}