// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerVitalsBase.h"

APlayerVitalsBase::APlayerVitalsBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerVitalsBase::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerVitalsBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerVitalsBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerVitalsBase::OnEnemyReachEnd_Implementation(AActor* enemyActor, EnemyType enemyType, double damage) { }
void APlayerVitalsBase::OnGatherResource_Implementation(ResourceType resource, int amount) { }
