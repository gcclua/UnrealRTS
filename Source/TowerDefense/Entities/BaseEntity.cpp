// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseEntity.h"

ABaseEntity::ABaseEntity()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseEntity::Register()
{
	auto entityManager = Cast<AEntityManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AEntityManager::StaticClass()));
	entityManager->RegisterEntity(this);
}

void ABaseEntity::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ABaseEntity::Register, 0.5f, false);
	
	OnInit();
}

void ABaseEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OnUpdate();
}

void ABaseEntity::OnDestroy()
{
	auto entityManager = Cast<AEntityManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AEntityManager::StaticClass()));
	entityManager->UnRegisterEntity(this);
}

AActor* IEntity::GetActor()
{
	return dynamic_cast<AActor*>(this);
}

void ABaseEntity::OnUpdate_Implementation() { }
void ABaseEntity::OnInit_Implementation() { }