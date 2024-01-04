// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

private:
	ResourceFarmerState state;
	double nextFarmTime;
	UPROPERTY() APlayerVitalsBase* playerVitals;

public:	
	UPROPERTY(EditAnywhere, Category = "ResourceFarmer")
	ResourceType ResourceType;

	UPROPERTY(EditAnywhere, Category = "ResourceFarmer")
	float GenerateTime = 5;
	
public:
	AResourceFarmerBase();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartFarming();

	virtual bool IsSelectable() override;
	virtual EntityType GetEntityType() override;
};
