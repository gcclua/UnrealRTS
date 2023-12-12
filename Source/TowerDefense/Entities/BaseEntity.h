// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "TowerDefense/Interfaces/IEntity.h"
#include "CoreMinimal.h"
#include "TowerDefense/UI/MiniMap.h"
#include "TowerDefense/Systems/EntityManager.h"
#include "GameFramework/Actor.h"
#include "BaseEntity.generated.h"

UCLASS(ABSTRACT)
class TOWERDEFENSE_API ABaseEntity : public AActor, public IEntity
{
	GENERATED_BODY()

private:
	void Register();
public:	
	ABaseEntity();
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInit();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnUpdate();

	UFUNCTION(BlueprintCallable, BlueprintCallable)
	void OnDestroy();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;

protected:
	virtual void BeginPlay() override;
};
