#pragma once
#include "IUnit.h"
#include "TowerDefense/Interfaces/IMouseInteraction.h"
#include "TowerDefense/UI/HUDBase.h"
#include "UnitManager.generated.h"

UCLASS()
class AUnitManager : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<IUnit*> selectedUnits;

	UPROPERTY()
	TArray<IUnit*> pendingUnits;

	UPROPERTY()
	UHUDBase* hud;
	TScriptInterface<IMouseInteractionInterface> mouseInteraction;
	UPROPERTY()
	APlayerController* playerController;
	
	double mouseDownTime;

	void OnLeftClickDown();
	void OnLeftClickUp();

	AUnitManager();

	TArray<FVector> GenerateHoneycombDestinations(const FVector& center, int32 unitCount, float hexSize) const;
	
public:
	UFUNCTION(BlueprintCallable)
	void Setup(UHUDBase* _hud, TScriptInterface<IMouseInteractionInterface> _mouseInteraction, APlayerController* _playerController);

	void AddCurrentlySelectedUnit(IUnit* _unit);
	void RemoveCurrentlySelectedUnit(IUnit* _unit);
};
