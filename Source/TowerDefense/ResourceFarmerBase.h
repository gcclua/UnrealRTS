// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IEntity.h"
#include "Enums/ResourceType.h"
#include "GameFramework/Actor.h"
#include "ResourceFarmerBase.generated.h"

UCLASS(Abstract)
class TOWERDEFENSE_API AResourceFarmerBase : public AActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere)
	ResourceType ResourceType;

	UPROPERTY(EditAnywhere)
	float GenerateTime = 5;
	
public:
	AResourceFarmerBase();
	virtual void Tick(float DeltaTime) override;
};
