// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResourceFarmerLevelStats.h"
#include "TowerDefense/Interfaces/IEntity.h"
#include "TowerDefense/Enums/ResourceType.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "ResourceFarmerState.h"
#include "TowerDefense/Core/PlayerVitalsBase.h"
#include "TowerDefense/Entities/Buildings/BuildingBase.h"
#include "ResourceFarmerBase.generated.h"

UCLASS()
class TOWERDEFENSE_API AResourceFarmerBase : public ABuildingBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	
	ResourceFarmerState state;
	double nextFarmTime;
	int generateAmount;
	float generateTime;
	UPROPERTY() APlayerVitalsBase* playerVitals;

public:	
	UPROPERTY(EditAnywhere, Category = "ResourceFarmer")
	ResourceType ResourceType;

	UPROPERTY(EditAnywhere, Category = "ResourceFarmer")
	TArray<FResourceFarmerLevelStats> LevelStats;

public:
	AResourceFarmerBase();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartFarming();

	// IEntity
	virtual EntityType GetEntityType() override;
	
	// IBuilding
	virtual void UpgradeToLevel(int _level) override;
	virtual int MaxLevel() override;
	virtual int NextCostMoney() override;
};
