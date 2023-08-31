// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Interfaces/IEntity.h"
#include "../UI/MiniMap.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefense/UI/MouseInteractionBase.h"
#include "EntityManager.generated.h"

UCLASS()
class TOWERDEFENSE_API AEntityManager : public AActor
{
	GENERATED_BODY()
	
private: // vars
	TArray<IEntity*> entities;
	UPROPERTY() UMiniMap* minimap;
	UPROPERTY() UMouseInteractionBase* mouseInteraction;

protected:
	virtual void BeginPlay() override;

public: // methods
	AEntityManager();
	virtual void Tick(float DeltaTime) override;
	
	virtual void RegisterEntity(IEntity* entity);
	virtual void UnRegisterEntity(IEntity* entity);

	UFUNCTION(BlueprintCallable)
	void Setup(UMiniMap* _minimap, UMouseInteractionBase* _mouseInteraction);
};
