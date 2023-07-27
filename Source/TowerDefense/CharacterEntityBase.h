// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "IEntity.h"
#include "MiniMap.h"
#include "GameFramework/Character.h"
#include "CharacterEntityBase.generated.h"

UCLASS()
class TOWERDEFENSE_API ACharacterEntityBase : public ACharacter, public IEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterEntityBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
