// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "../Interfaces/IEntity.h"
#include "../UI/MiniMap.h"
#include "GameFramework/Character.h"
#include "../Systems/EntityManager.h"
#include "CharacterEntityBase.generated.h"

UCLASS(ABSTRACT)
class TOWERDEFENSE_API ACharacterEntityBase : public ACharacter, public IEntity
{
	GENERATED_BODY()

private:
	bool registered = false;
	bool unRegistered = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Register();
	void UnRegister();

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
