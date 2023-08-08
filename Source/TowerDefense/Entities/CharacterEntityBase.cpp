// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterEntityBase.h"

ACharacterEntityBase::ACharacterEntityBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACharacterEntityBase::Register()
{
	auto entityManager = Cast<AEntityManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AEntityManager::StaticClass()));
	entityManager->RegisterEntity(this);
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
	auto entityManager = Cast<AEntityManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AEntityManager::StaticClass()));
	entityManager->UnRegisterEntity(this);
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