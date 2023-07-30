// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IEntity.h"
#include "MiniMap.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "EntityManager.generated.h"

UCLASS()
class TOWERDEFENSE_API AEntityManager : public AActor
{
	GENERATED_BODY()
	
private: // vars
	TArray<IEntity*> entities;
	UPROPERTY()
	class UMiniMap* minimap;

protected:
	virtual void BeginPlay() override;

public: // methods
	AEntityManager();
	virtual void Tick(float DeltaTime) override;
	
	virtual void RegisterEntity(IEntity* entity);
	virtual void UnRegisterEntity(IEntity* entity);
};
