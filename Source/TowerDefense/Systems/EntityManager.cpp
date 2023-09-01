// Fill out your copyright notice in the Description page of Project Settings.

#include "EntityManager.h"
#include "TowerDefense/UI/MouseInteractionBase.h"

AEntityManager::AEntityManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEntityManager::BeginPlay()
{
	Super::BeginPlay();
}

void AEntityManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	minimap->OnUpdate();
	mouseInteraction->OnUpdate();
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

void AEntityManager::Setup(UMiniMap* _minimap, UMouseInteractionBase* _mouseInteraction)
{
	minimap = _minimap;
	mouseInteraction = _mouseInteraction;
}

void AEntityManager::UpdateSelectedEntitiesInRange(FVector topLeft, FVector bottomRight)
{
	for (int i = 0; i < entities.Num(); i++)
	{
		IEntity* entity = entities[i];
		if (!entity || !entity->IsSelectable())
			continue;

		AActor* actor = entity->GetActor();
		UStaticMeshComponent* selectionMesh = entity->Execute_GetSelectionMesh(actor);
		if (!selectionMesh)
		    continue;
		
		const FVector location = actor->GetActorLocation();
		const FVector2d point = FVector2d(location.X, location.Y);

		const bool shouldBeSelected = point.X <= topLeft.X && point.X >= bottomRight.X
							       && point.Y <= topLeft.Y && point.Y >= bottomRight.Y;

		if (shouldBeSelected != selectionMesh->IsVisible())
			selectionMesh->SetVisibility(shouldBeSelected);
	}
}

void AEntityManager::DeselectAllEntities()
{
	for (int i = 0; i < entities.Num(); i++)
	{
		IEntity* entity = entities[i];
		if (!entity || !entity->IsSelectable())
			continue;

		UStaticMeshComponent* selectionMesh = entity->Execute_GetSelectionMesh(entity->GetActor());
		if (!selectionMesh)
			continue;
		
		selectionMesh->SetVisibility(false);
	}
}
