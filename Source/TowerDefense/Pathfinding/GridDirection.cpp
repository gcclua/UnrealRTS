#include "GridDirection.h"

const GridDirection GridDirection::None(0, 0);
const GridDirection GridDirection::North(0, 1);
const GridDirection GridDirection::South(0, -1);
const GridDirection GridDirection::East(1, 0);
const GridDirection GridDirection::West(-1, 0);
const GridDirection GridDirection::NorthEast(1, 1);
const GridDirection GridDirection::NorthWest(-1, 1);
const GridDirection GridDirection::SouthEast(1, -1);
const GridDirection GridDirection::SouthWest(-1, -1);

const TArray<GridDirection> GridDirection::CardinalDirections = {
	GridDirection::North,
	GridDirection::East,
	GridDirection::South,
	GridDirection::West
};

const TArray<GridDirection> GridDirection::CardinalAndIntercardinalDirections = {
	GridDirection::North,
	GridDirection::NorthEast,
	GridDirection::East,
	GridDirection::SouthEast,
	GridDirection::South,
	GridDirection::SouthWest,
	GridDirection::West,
	GridDirection::NorthWest
};

const TArray<GridDirection> GridDirection::AllDirections = {
	GridDirection::None,
	GridDirection::North,
	GridDirection::NorthEast,
	GridDirection::East,
	GridDirection::SouthEast,
	GridDirection::South,
	GridDirection::SouthWest,
	GridDirection::West,
	GridDirection::NorthWest
};