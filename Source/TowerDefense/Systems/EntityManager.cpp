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
	// first get the area of the quad itself
	const double halfQuadA = AreaOfTriangle(bottomLeft, topLeft, bottomRight);
	const double halfQuadB = AreaOfTriangle(topLeft, topRight, bottomRight);

	const double areaQuad = halfQuadA + halfQuadB;

	// get the area of the 4 triangles from the point to all the quads corners
	const double pointAreaA = AreaOfTriangle(point, bottomLeft, topLeft);
	const double pointAreaB = AreaOfTriangle(point, topLeft, topRight);
	const double pointAreaC = AreaOfTriangle(point, topRight, bottomRight);
	const double pointAreaD = AreaOfTriangle(point, bottomRight, bottomLeft);
	
	const double pointArea = pointAreaA + pointAreaB + pointAreaC + pointAreaD;

	// ignore close to 0
	if (areaQuad <= 0.0001f)
		return false;

	// is outside of the area of the 4 triangles is greater than the area of the quad
	const bool outSide = pointArea > areaQuad;
	return !outSide;
}

double AEntityManager::AreaOfTriangle(FVector2d point0, FVector2d point1, FVector2d point2)
{
	const double t1 = point1.Y - point2.Y;
	const double t2 = point1.X - point2.X;
	const double t3 = (point1.X * point2.Y) - (point1.Y * point2.X);
	const double determinant = (point0.X * t1) + (-point0.Y * t2) + t3;

	return FMath::Abs(determinant) * 0.5;
}


