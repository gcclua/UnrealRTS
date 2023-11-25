#pragma once
#include "GridDirection.h"
#include "IntVectorTypes.h"

using namespace UE::Geometry;

struct Cell
{
public:
	FVector worldPos;
	FVector2i gridIndex;
	BYTE cost;
	USHORT bestCost;
	GridDirection bestDirection;

	Cell();
	void Setup(FVector _worldPos, FVector2i _gridIndex);
	~Cell();

	void IncreaseCost(int amount);
};
