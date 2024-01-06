// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Interfaces/IEntity.h"
#include "../UI/MiniMap.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefense/Entities/Units/IUnit.h"
#include "TowerDefense/Entities/Units/UnitManager.h"
#include "EntityManager.generated.h"

class UMouseInteractionBase;

UCLASS()
class TOWERDEFENSE_API AEntityManager : public AActor
{
	GENERATED_BODY()
	
private: // vars
	static AEntityManager* Instance;
	
	TArray<IEntity*> entities;
	TSet<IEntity*> selectedEntities;
	
	UPROPERTY() UMiniMap* minimap;
	UPROPERTY() UMouseInteractionBase* mouseInteraction;
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
	void Setup(UMiniMap* _minimap, UMouseInteractionBase* _mouseInteraction, AUnitManager* _unitManager);

	void UpdateSelectedEntitiesInRange(const FVector topLeft, const FVector bottomRight, const FVector bottomLeft, const FVector topRight);
	void DeselectAllEntities();
	
	static bool PointInsideQuadrilateral(const FVector2d point, const FVector2d topLeft, const FVector2d topRight, const FVector2d bottomLeft, const FVector2d bottomRight);
	static double AreaOfTriangle(const FVector2d point0, const FVector2d point1, const FVector2d point2);
};
