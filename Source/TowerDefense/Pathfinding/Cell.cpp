#include "Cell.h"

Cell::Cell() : cost(0), bestCost(USHORT_MAX)
{

}

void Cell::Setup(FVector _worldPos, FVector2i _gridIndex)
{
	worldPos = _worldPos;
	gridIndex = _gridIndex;
	cost = 0;
	bestCost = USHORT_MAX;
}

Cell::~Cell()
{
	// destructor stuff
}

void Cell::IncreaseCost(int amount)
{
	if (cost == BYTE_MAX)
		return;
	
	if (amount + cost >= BYTE_MAX)
		cost = BYTE_MAX;
	else
		cost += amount;
}
