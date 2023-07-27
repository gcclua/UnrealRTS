// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IEntity.h"
#include "Blueprint/UserWidget.h"
#include "MiniMap.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UMiniMap : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void OnUpdate();

	void RegisterEntity(IEntity* entity);
	void UnRegisterEntity(IEntity* entity);
	
	virtual bool Initialize() override;
};
