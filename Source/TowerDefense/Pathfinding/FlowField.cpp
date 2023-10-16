#include "FlowField.h"

#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

FlowField::FlowField() : cellRadius(0)
{
}

void FlowField::Init(float _cellRadius, FVector2i _gridSize, UWorld* _world, const TArray<TEnumAsByte<EObjectTypeQuery>> _wallCollision)
{
	if (!_world) return;
	
	cellRadius = _cellRadius;
	world = MakeWeakObjectPtr(_world);
	gridSize = _gridSize;
	wallCollision = _wallCollision;

	grid = MakeShared<TArray2D<TSharedPtr<Cell>>>();
	grid->Init(MakeShared<Cell>(), gridSize.X, gridSize.Y);

	const float cellDiameter = cellRadius * 2;
	for (int x = 0; x < gridSize.X; x++)
	{
		for (int y = 0; y < gridSize.Y; y++)
		{
			const FVector worldPos = FVector(cellDiameter * x + cellRadius, cellDiameter * y + cellRadius, 100);
			const TSharedPtr<Cell> curCell = grid->GetElement(x, y);
			curCell->Setup(worldPos, FVector2i(x, y));
		}
	}
}

FlowField::~FlowField()
{

}

void FlowField::CreateCostField()
{
	for (int x = 0; x < gridSize.X; x++)
	{
		for (int y = 0; y < gridSize.Y; y++)
		{
			TSharedPtr<Cell> cell = grid->GetElement(x, y);
			FHitResult outHit;

			const bool hasHitWall = UKismetSystemLibrary::SphereTraceSingleForObjects(world.Get(), cell->worldPos, cell->worldPos, cellRadius * 1.5f, wallCollision,
				false, TArray<AActor*>(), EDrawDebugTrace::None, outHit, false);

			if (hasHitWall)
			{
				cell->IncreaseCost(255);
			}
		}
	}
}

void FlowField::CreateIntegrationField(const TSharedPtr<Cell>& _destinationCell)
{
	destinationCell = _destinationCell;
	
	TQueue<TSharedPtr<Cell>> cellsToCheck;
	cellsToCheck.Enqueue(destinationCell);

	while (!cellsToCheck.IsEmpty())
	{
		TSharedPtr<Cell> curCell;
		if (cellsToCheck.Dequeue(curCell))
		{
			TArray<TSharedPtr<Cell>> curNeighbours = GetNeighboringCells_Cardinals(curCell);
			for (const TSharedPtr<Cell> curNeighbour : curNeighbours)
			{
				if (curNeighbour->cost == BYTE_MAX) continue;

				if (curNeighbour->cost + curCell->bestCost < curNeighbour->bestCost)
				{
					curNeighbour->bestCost = static_cast<USHORT>(curNeighbour->cost + curCell->bestCost);
				}
			}
		}
	}
}

TArray<TSharedPtr<Cell>> FlowField::GetNeighboringCells_Cardinals(const TSharedPtr<Cell>& cell) const
{
	TArray<TSharedPtr<Cell>> neighbors;

	if (cell.IsValid())
	{
		// Calculate the grid coordinates of the neighboring cells
		const int x = cell->gridIndex.X;
		const int y = cell->gridIndex.Y;

		// Check and add the neighboring cells in the cardinal directions
		AddNeighbor(neighbors, x - 1, y); // Left
		AddNeighbor(neighbors, x + 1, y); // Right
		AddNeighbor(neighbors, x, y - 1); // Up
		AddNeighbor(neighbors, x, y + 1); // Down
	}

	return neighbors;
}

void FlowField::AddNeighbor(TArray<TSharedPtr<Cell>>& neighbors, const int x, const int y) const
{
	// Ensure the coordinates are within the grid boundaries
	if (x >= 0 && x < gridSize.X && y >= 0 && y < gridSize.Y)
	{
		neighbors.Add(grid->GetElement(x, y));
	}
}
