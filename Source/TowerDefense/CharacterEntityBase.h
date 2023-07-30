// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "IEntity.h"
#include "MiniMap.h"
#include "GameFramework/Character.h"
#include "EntityManager.h"
#include "CharacterEntityBase.generated.h"

UCLASS()
class TOWERDEFENSE_API ACharacterEntityBase : public ACharacter, public IEntity
{
	GENERATED_BODY()

private:
	void Register();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInit();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnUpdate();

	UFUNCTION(BlueprintCallable, BlueprintCallable)
	void OnDestroy();
	
	ACharacterEntityBase();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
