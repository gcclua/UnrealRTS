// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefense/Interfaces/IEntity.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefense/Entities/Units/IUnit.h"
#include "TowerDefense/Entities/Units/UnitManager.h"
#include "TowerDefense/Interfaces/IEntityManager.h"
#include "TowerDefense/Interfaces/IMinimap.h"
#include "TowerDefense/Interfaces/IMouseInteraction.h"
#include "EntityManager.generated.h"

UCLASS()
class TOWERDEFENSE_API AEntityManager : public AActor, public IEntityManagerInterface
{
	GENERATED_BODY()
	
private: // vars
	static AEntityManager* Instance;
	
	TArray<IEntity*> entities;
	TSet<IEntity*> selectedEntities;
	
	TScriptInterface<IMinimapInterface> minimap;
	TScriptInterface<IMouseInteractionInterface> mouseInteraction;
	UPROPERTY() AUnitManager* unitManager;
	
protected:
	virtual void BeginPlay() override;

public: // methods
	AEntityManager();
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;
	
	virtual void RegisterEntity(IEntity* entity);
	virtual void UnRegisterEntity(IEntity* entity);

	static AEntityManager* GetInstance();

	UFUNCTION(BlueprintCallable)
	void Setup(TScriptInterface<IMinimapInterface> _minimap, TScriptInterface<IMouseInteractionInterface> _mouseInteraction, AUnitManager* _unitManager);

	virtual void UpdateSelectedEntitiesInRange(const FVector topLeft, const FVector bottomRight, const FVector bottomLeft, const FVector topRight) override;
	virtual void DeselectAllEntities() override;
	virtual void SelectEntity(IEntity* entity) override;
	virtual void DeselectEntity(IEntity* entity) override;
	virtual bool IsEntitySelected(IEntity* entity) const override;
	
	static bool PointInsideQuadrilateral(const FVector2d point, const FVector2d topLeft, const FVector2d topRight, const FVector2d bottomLeft, const FVector2d bottomRight);
	static double AreaOfTriangle(const FVector2d point0, const FVector2d point1, const FVector2d point2);
};
