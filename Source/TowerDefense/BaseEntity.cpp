// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseEntity.h"

ABaseEntity::ABaseEntity()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseEntity::BeginPlay()
{
	Super::BeginPlay();
	OnInit();
}

void ABaseEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OnUpdate();
}

void ABaseEntity::OnUpdate_Implementation() { }
void ABaseEntity::OnInit_Implementation() { }
