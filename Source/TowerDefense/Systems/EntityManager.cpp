// Fill out your copyright notice in the Description page of Project Settings.

#include "EntityManager.h"

#include "GeomTools.h"
#include "MeshUtilitiesCommon.h"
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

void AEntityManager::UpdateSelectedEntitiesInRange(FVector topLeft, FVector bottomRight, FVector bottomLeft, FVector topRight)
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
		
		const bool shouldBeSelected = PointInsideQuadrilateral(point,
										  FVector2d(topLeft.X, topLeft.Y),
									     FVector2d(topRight.X, topRight.Y),
								       FVector2d(bottomLeft.X, bottomLeft.Y),
									  FVector2d(bottomRight.X, bottomRight.Y));

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

// https://stackoverflow.com/a/16260220
bool AEntityManager::PointInsideQuadrilateral(FVector2d point, FVector2d topLeft, FVector2d topRight,
	FVector2d bottomLeft, FVector2d bottomRight)
{
	const float pointAreaA = AreaOfTriangle(point, bottomLeft, topLeft);
	const float pointAreaB = AreaOfTriangle(point, topLeft, topRight);
	const float pointAreaC = AreaOfTriangle(point, topRight, bottomRight);
	const float pointAreaD = AreaOfTriangle(point, bottomRight, bottomLeft);
	const float pointArea = pointAreaA + pointAreaB + pointAreaC + pointAreaD;

	const float halfQuadA = AreaOfTriangle(bottomLeft, topLeft, bottomRight);
	const float halfQuadB = AreaOfTriangle(topLeft, topRight, bottomRight);

	const float areaQuad = halfQuadA + halfQuadB;

	if (areaQuad <= 0.01f)
		return false;
	
	const bool outSide = pointArea > areaQuad;
	
	return !outSide;
}

float AEntityManager::AreaOfTriangle(FVector2d point0, FVector2d point1, FVector2d point2)
{
	const float A = FVector2d::Distance(point0, point1);
	const float B = FVector2d::Distance(point1, point2);
	const float C = FVector2d::Distance(point2, point0);
	
	const float S = (A + B + C) * 0.5;

	const float area = FMath::Sqrt(S * (S - A) * (S - B) * (S - C));

	return area;
}


