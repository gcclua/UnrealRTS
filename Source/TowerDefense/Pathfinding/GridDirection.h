#pragma once

#include "CoreMinimal.h"
#include "IntVectorTypes.h"

using namespace UE::Geometry;

struct GridDirection
{
public:
	FVector2i Vector;

	GridDirection(int x, int y) : Vector(x, y) {}
	GridDirection() : Vector(0, 0) {}
	
	static GridDirection GetDirectionFromV2D(FVector2i vector)
	{
		for (const GridDirection& Direction : CardinalAndIntercardinalDirections)
		{
			if (Direction.Vector == vector)
			{
				return Direction;
			}
		}

		return None;
	}
	static const GridDirection None;
	static const GridDirection North;
	static const GridDirection South;
	static const GridDirection East;
	static const GridDirection West;
	static const GridDirection NorthEast;
	static const GridDirection NorthWest;
	static const GridDirection SouthEast;
	static const GridDirection SouthWest;

	static const TArray<GridDirection> CardinalDirections;
	static const TArray<GridDirection> CardinalAndIntercardinalDirections;
	static const TArray<GridDirection> AllDirections;
};
