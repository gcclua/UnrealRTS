// Fill out your copyright notice in the Description page of Project Settings.

#include "EntityManager.h"
#include "Logger.h"

AEntityManager::AEntityManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEntityManager::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<UUserWidget*> widgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), widgets, UMiniMap::StaticClass());
	if (widgets.Num() > 0)
	{
		minimap = Cast<UMiniMap>(widgets[0]);
		//minimap->Setup(GetWorld()->GetFirstPlayerController());
	}
}

void AEntityManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	minimap->OnUpdate();
}

void AEntityManager::RegisterEntity(IEntity* entity)
{
	if (!entities.Contains(entity))
	{
		entities.Add(entity);
		minimap->RegisterActor(entity->GetActor());
	}
}

void AEntityManager::UnRegisterEntity(IEntity* entity)
{
	if (entities.Contains(entity))
	{
		entities.Remove(entity);
		minimap->UnRegisterActor(entity->GetActor());
	}
}
