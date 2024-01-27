// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingManager.h"

ABuildingManager::ABuildingManager()
{

}

void ABuildingManager::Setup(TScriptInterface<IHUDInterface> _hud, TScriptInterface<IEntityManagerInterface> _entityManager, APlayerController* _playerController)
{
	hud = _hud;
	entityManager = _entityManager;
	playerController = _playerController;
	
	_playerController->InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &ABuildingManager::OnLeftClickDown);
}

void ABuildingManager::OnLeftClickDown()
{
	if (selectedBuilding != nullptr)
	{
		entityManager->DeselectEntity(selectedBuilding.Get());
		selectedBuilding = nullptr;
	}

	bool buildingSelected = false;
	
	FHitResult hit;
	playerController->GetHitResultUnderCursorForObjects(
		CollisionMask,
		true,
		hit);

	AActor* hitActor = hit.GetActor();
	if (hitActor != nullptr && hitActor->IsA(ABuildingBase::StaticClass()))
	{
		ABuildingBase* building = Cast<ABuildingBase>(hitActor);
		if (building == nullptr || building->IsConstruction)
			return;
		
		const bool selected = entityManager->IsEntitySelected(building);
		if (!selected)
		{
			entityManager->SelectEntity(building);
			selectedBuilding = building;
		}
	}
}
