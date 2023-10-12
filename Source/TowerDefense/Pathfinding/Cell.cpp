#include "Cell.h"

Cell::Cell()
{
}

Cell::Cell(FVector _worldPos, FVector2i _gridIndex)
{
	worldPos = _worldPos;
	gridIndex = _gridIndex;
}

Cell::~Cell()
{
	// destructor stuff
}

void Cell::IncreaseCost(int amount)
{
	constexpr short MAX_VALUE = 255;
	if (cost == MAX_VALUE)
		return;
	
	if (amount + cost >= MAX_VALUE)
		cost = MAX_VALUE;
	else
		cost += amount;
}
