// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseEntity.h"

ABaseEntity::ABaseEntity()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseEntity::Register()
{
	if (registered)
		return;
	
	AEntityManager* entityManager = AEntityManager::GetInstance();
	if (entityManager != nullptr)
		entityManager->RegisterEntity(this);
	registered = true;
}

void ABaseEntity::UnRegister()
{
	if (unRegistered)
		return;
	
	AEntityManager* entityManager = AEntityManager::GetInstance();
	if (entityManager != nullptr)
		entityManager->UnRegisterEntity(this);
	unRegistered = true;
}

void ABaseEntity::BeginPlay()
{
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ABaseEntity::Register, 0.5f, false);
	
	OnInit();
	
	Super::BeginPlay();
}

void ABaseEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OnUpdate();
}

void ABaseEntity::OnDestroy()
{
	UnRegister();
}

void ABaseEntity::OnUpdate_Implementation() { }
void ABaseEntity::OnInit_Implementation() { }
