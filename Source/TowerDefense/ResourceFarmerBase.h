// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResourceFarmerBase.generated.h"

UCLASS(Abstract)
class TOWERDEFENSE_API AResourceFarmerBase : public AActor
{
	GENERATED_BODY()
	


protected:
	virtual void BeginPlay() override;

public:	
	
	
public:
	AResourceFarmerBase();
	virtual void Tick(float DeltaTime) override;

};
