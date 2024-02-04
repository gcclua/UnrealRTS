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

	UObject* panel = hud->GetPanel(HUDPanelType::Building);
	if (panel != nullptr)
		buildingsHudPanel = TScriptInterface<IHUDPanelBuildingsInterface>(panel);
}

void ABuildingManager::OnLeftClickDown()
{
	const TWeakObjectPtr<ABuildingBase> prevSelectedBuilding = selectedBuilding;
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

		buildingSelected = true;
		selectedBuilding = building;
		
		if (!entityManager->IsEntitySelected(building))
			entityManager->SelectEntity(building);

		if (!hudPanelEnabled)
		{
			if (hud != nullptr && buildingsHudPanel != nullptr)
			{
				hud->SetHUDPanelVisibility(HUDPanelType::Building, true);
				buildingsHudPanel->PopulateData(selectedBuilding.Get());
			}

			hudPanelEnabled = true;
		}
		else if (prevSelectedBuilding != selectedBuilding)
		{
			if (buildingsHudPanel != nullptr)
			{
				hud->SetHUDPanelVisibility(HUDPanelType::Building, true);
				buildingsHudPanel->PopulateData(selectedBuilding.Get());
			}
		}
	}

	if (!buildingSelected && hudPanelEnabled)
	{
		selectedBuilding = nullptr;
		hud->SetHUDPanelVisibility(HUDPanelType::Building, false);
		hudPanelEnabled = false;
	}
}
