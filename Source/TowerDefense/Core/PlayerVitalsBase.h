// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraMovement.h"
#include "../Enums/ResourceType.h"
#include "GameFramework/Pawn.h"
#include "TowerDefense/Enums/EnemyTypes.h"
#include "TowerDefense/UI/HUDBase.h"
#include "PlayerVitalsBase.generated.h"

UCLASS()
class TOWERDEFENSE_API APlayerVitalsBase : public APawn
{
	GENERATED_BODY()

protected:
	static APlayerVitalsBase* Instance;
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVitals")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVitals")
	int Metal;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVitals")
	int Stone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVitals")
	int Wood;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVitals")
	int Money;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVitals")
	UInputComponent* myInputComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVitals")
	UHUDBase* HUD;
	
	APlayerVitalsBase();
	static APlayerVitalsBase* GetInstance();
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnGatherResource(ResourceType resource, int amount = 1);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnEnemyReachEnd(AActor* enemyActor, EnemyType enemyType, double damage);

	int GetMoney() const;
	void SetMoney(int newMoney);
	void AddMoney(int amount);
};
