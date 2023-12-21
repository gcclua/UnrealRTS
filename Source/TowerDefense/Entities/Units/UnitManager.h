#pragma once
#include "IUnit.h"
#include "TowerDefense/UI/HUDBase.h"
#include "UnitManager.generated.h"

class UMouseInteractionBase;

UCLASS()
class AUnitManager : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<IUnit*> selectedUnits;

	UPROPERTY()
	UHUDBase* hud;
	UPROPERTY()
	UMouseInteractionBase* mouseInteraction;
	UPROPERTY()
	APlayerController* playerController;
	
	double mouseDownTime;

	void OnLeftClickDown();
	void OnLeftClickUp();

	AUnitManager();
	
public:
	UFUNCTION(BlueprintCallable)
	void Setup(UHUDBase* _hud, UMouseInteractionBase* _mouseInteraction, APlayerController* _playerController);

	void AddCurrentlySelectedUnit(IUnit* _unit);
	void RemoveCurrentlySelectedUnit(IUnit* _unit);
};
