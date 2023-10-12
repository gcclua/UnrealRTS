#include "FlowField.h"

#include "Kismet/KismetSystemLibrary.h"

FlowField::FlowField()
{
}

void FlowField::Init(float _cellRadius, FVector2i _gridSize, UWorld* _world, TArray<TEnumAsByte<EObjectTypeQuery>> _wallCollision)
{
	if (!_world) return;
	
	cellRadius = _cellRadius;
	world = MakeWeakObjectPtr(_world);
	gridSize = _gridSize;
	wallCollision = _wallCollision;

	grid = MakeShared<TArray2D<Cell>>();
	grid->Init(Cell(), gridSize.X, gridSize.Y);

	const float cellDiameter = cellRadius * 2;
	for (int x = 0; x < gridSize.X; x++)
	{
		for (int y = 0; y < gridSize.Y; y++)
		{
			const FVector worldPos = FVector(cellDiameter * x + cellRadius, cellDiameter * y + cellRadius, 0);
			grid->SetElement(x, y, Cell(worldPos, FVector2i(x, y)));
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
			Cell cell = grid->GetElement(x, y);
			FHitResult outHit;
			UKismetSystemLibrary::SphereTraceSingleForObjects(world.Get(), cell.worldPos, cell.worldPos, cellRadius, wallCollision,
				false, TArray<AActor*>(), EDrawDebugTrace::None, outHit, false);
		}
	}
}
