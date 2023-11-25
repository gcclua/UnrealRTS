#include "FlowField.h"

#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

FlowField::FlowField() : cellRadius(0)
{
}

void FlowField::Init(float _cellRadius, FVector2i _gridSize, UWorld* _world, const TArray<TEnumAsByte<EObjectTypeQuery>> _wallCollision)
{
	if (!_world) return;

	UE_LOG(LogTemp, Warning, TEXT("Flowfield init"));
	
	cellRadius = _cellRadius;
	cellDiameter = cellRadius * 2;
	world = MakeWeakObjectPtr(_world);
	gridSize = _gridSize;
	wallCollision = _wallCollision;

	grid = MakeShared<TArray2D<TSharedPtr<Cell>>>();

	TSharedPtr<Cell> initCell = MakeShared<Cell>();
	grid->Init(initCell, gridSize.X, gridSize.Y);
	
	for (int x = 0; x < gridSize.X; x++)
	{
		for (int y = 0; y < gridSize.Y; y++)
		{
			const FVector worldPos = FVector(cellDiameter * x + cellRadius, cellDiameter * y + cellRadius, 100);
			
			TSharedPtr<Cell> curCell = MakeShared<Cell>();
			curCell->Setup(worldPos, FVector2i(x, y));
			grid->SetElement(x, y, curCell);
		}
	}

	initCell = nullptr;
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

			const FVector worldPos = cell->worldPos;
			
			const bool hasHitWall = UKismetSystemLibrary::SphereTraceSingleForObjects(world.Get(), worldPos, worldPos, cellRadius * 1.5f, wallCollision,
				false, TArray<AActor*>(), EDrawDebugTrace::None, outHit, false);

			if (hasHitWall)
			{
				cell->IncreaseCost(BYTE_MAX);
			}

			//DrawDebugCircle(world.Get(), cell->worldPos, cellRadius, 32, hasHitWall ? FColor::Red : FColor::Blue,true,
			//	-1,0,2.0f,FVector(0, 1, 0),FVector(1, 0, 0));
		}
	}
}

void FlowField::CreateIntegrationField(const TSharedPtr<Cell>& _destinationCell)
{
	destinationCell = _destinationCell;
	destinationCell->cost = 0;
	destinationCell->bestCost = 0;

	UE_LOG(LogTemp, Warning, TEXT("Create integration field, destination index: (%d, %d)"), _destinationCell->gridIndex.X, _destinationCell->gridIndex.Y);
	
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
					cellsToCheck.Enqueue(curNeighbour);
				}
			}
		}
	}
}

TSharedPtr<Cell> FlowField::GetCellFromWorldPos(FVector worldPos) const
{
	const double percentX = FMath::Clamp(worldPos.X / (gridSize.X * cellDiameter), 0.0, 1.0);
	const double percentY = FMath::Clamp(worldPos.Y / (gridSize.Y * cellDiameter), 0.0, 1.0);

	const int x = FMath::Clamp(FMath::FloorToInt(gridSize.X * percentX), 0, gridSize.X - 1);
	const int y = FMath::Clamp(FMath::FloorToInt(gridSize.Y * percentY), 0, gridSize.Y - 1);

	return grid->GetElement(x, y);
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

void FlowField::DrawDebug()
{
	// r.DebugSafeZone.MaxDebugTextStringsPerActor 0
	FlushDebugStrings(world.Get());
	FlushPersistentDebugLines(world.Get());

	if (debugType == FlowFieldDebugType::None)
		return;
	
	for (int x = 0; x < gridSize.X; x++)
	{
		for (int y = 0; y < gridSize.Y; y++)
		{
			const TSharedPtr<Cell> cell = grid->GetElement(x, y);
			const FVector gridPos = cell->worldPos;

			constexpr float lifeTime = 50;

			FVector BoxExtent = FVector(cellRadius, cellRadius, 1.0f);
			FColor BoxColor = FColor::Black;
			DrawDebugBox(world.Get(), gridPos, BoxExtent, BoxColor, false, lifeTime, 0);
			
			//FString CostString = FString::Printf(TEXT("(%d, %d)"), x, y);
			FVector TextLocation = gridPos + FVector(cellRadius / 2.0f, cellRadius / 2.0f, 0);
			FColor TextColor = FColor::Black;
			float TextScale = 2.0f;
			
			// Draw the cost value as text or labels near the cell
			FString CostString = FString::Printf(TEXT("%d"), cell->cost);
			if (cell->cost >= 255)
			{
				TextColor = FColor::Red;
				TextScale = 1;
			}

			if (debugType == FlowFieldDebugType::IntegrationField)
			{
				CostString = FString::Printf(TEXT("%d"), cell->bestCost);
				if (cell->bestCost >= 255)
				{
					TextColor = FColor::Red;
					TextScale = 1;
				}
			}
			
			if (cell == destinationCell)
				TextColor = FColor::Blue;
			
			DrawDebugString(world.Get(), TextLocation, CostString, nullptr, TextColor, lifeTime, false, TextScale);
		}
	}
}

void FlowField::SetDebugType(FlowFieldDebugType type)
{
	UE_LOG(LogTemp, Warning, TEXT("Set Flowfield Debug Type: %d (1=cost, 2=integration)"), type);
	debugType = type;
}
