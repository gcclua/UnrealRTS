// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerDefense/Pathfinding/FlowField.h"
#include "UI/MouseInteractionBase.h"

#include "FlowFieldTester.generated.h"

UCLASS()
class TOWERDEFENSE_API AFlowFieldTester : public AActor
{
	GENERATED_BODY()

public:
	TSharedPtr<FlowField> flowField;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> WallCollision;
	
	// Sets default values for this actor's properties
	AFlowFieldTester();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Setup();

	void CreateFlowField();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	APlayerController* playerController;

	UPROPERTY()
	UMouseInteractionBase* mouseInteraction;

	bool hasSetup = false;
	bool flowFieldActive = false;
	bool mouseButtonDown = false;
	bool switchDebugButtonDown = false;
};
