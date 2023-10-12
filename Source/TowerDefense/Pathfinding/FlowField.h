#pragma once

#include "IntVectorTypes.h"
#include "Cell.h"
#include "TowerDefense/Utils/Array2D.h"

using namespace UE::Geometry;

class FlowField
{
public:
	TWeakObjectPtr<UWorld> world;

	TSharedPtr<TArray2D<Cell>> grid;
	FVector2i gridSize;
	float cellRadius;
	TArray<TEnumAsByte<EObjectTypeQuery>> wallCollision;

	FlowField();
	void Init(float _cellRadius, FVector2i _gridSize, UWorld* _world, TArray<TEnumAsByte<EObjectTypeQuery>> _wallCollision);

	~FlowField();

	void CreateCostField();
};
