// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterEntityBase.h"

ACharacterEntityBase::ACharacterEntityBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACharacterEntityBase::Register()
{
	if (registered)
		return;
	
	AEntityManager* entityManager = AEntityManager::GetInstance();
	if (entityManager != nullptr)
		entityManager->RegisterEntity(this);
	registered = true;
}

void ACharacterEntityBase::UnRegister()
{
	if (unRegistered)
		return;
	
	AEntityManager* entityManager = AEntityManager::GetInstance();
	if (entityManager != nullptr)
		entityManager->UnRegisterEntity(this);
	unRegistered = true;
}

void ACharacterEntityBase::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ACharacterEntityBase::Register, 0.5f, false);

	OnInit();
}

void ACharacterEntityBase::OnDestroy()
{
	UnRegister();
}

void ACharacterEntityBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OnUpdate();
}

void ACharacterEntityBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACharacterEntityBase::OnUpdate_Implementation() { }
void ACharacterEntityBase::OnInit_Implementation() { }