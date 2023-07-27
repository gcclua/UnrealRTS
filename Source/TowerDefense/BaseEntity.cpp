// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseEntity.h"

ABaseEntity::ABaseEntity()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseEntity::BeginPlay()
{
	Super::BeginPlay();

	auto minimap = Cast<UMiniMap>(UGameplayStatics::GetActorOfClass(GetWorld(), UMiniMap::StaticClass()));
	minimap->RegisterEntity(this);
	
	OnInit();
}

void ABaseEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OnUpdate();
}

void ABaseEntity::OnDestroy()
{
	auto minimap = Cast<UMiniMap>(UGameplayStatics::GetActorOfClass(GetWorld(), UMiniMap::StaticClass()));
	minimap->UnRegisterEntity(this);
}

AActor* IEntity::GetActor()
{
	return dynamic_cast<AActor*>(this);
}

void ABaseEntity::OnUpdate_Implementation() { }
void ABaseEntity::OnInit_Implementation() { }
