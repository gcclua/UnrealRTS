// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Enums/ResourceType.h"
#include "GameFramework/Pawn.h"
#include "PlayerVitalsBase.generated.h"

UCLASS()
class TOWERDEFENSE_API APlayerVitalsBase : public APawn
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	APlayerVitalsBase();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnGatherResource(ResourceType resource, int amount = 1);
};
