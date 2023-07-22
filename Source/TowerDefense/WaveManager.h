// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wave.h"

#include "EnemySpawner.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveManager.generated.h"

UCLASS()
class TOWERDEFENSE_API AWaveManager : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	// properties
	UPROPERTY(EditAnywhere)
	AEnemySpawner* EnemySpawner;
	
	UPROPERTY(EditAnywhere)
	TArray<FWave> Waves;

	// mono
	AWaveManager();
	virtual void Tick(float DeltaTime) override;

	void StartSpawning();

private:
	int waveIndex;
	bool isDone;
	float currentTime;
	bool hasStarted;
};
