// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraMovement.h"
#include "../Enums/ResourceType.h"
#include "GameFramework/Pawn.h"
#include "TowerDefense/Enums/EnemyTypes.h"
#include "PlayerVitalsBase.generated.h"

UCLASS()
class TOWERDEFENSE_API APlayerVitalsBase : public APawn
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputComponent* myInputComponent;
	
	APlayerVitalsBase();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnGatherResource(ResourceType resource, int amount = 1);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnEnemyReachEnd(AActor* enemyActor, EnemyType enemyType, double damage);
};
