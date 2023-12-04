// Fill out your copyright notice in the Description page of Project Settings.

#include "FlowFieldTester.h"
#include "TimerManager.h"
#include "TowerDefense/Pathfinding/FlowFieldDebugType.h"

AFlowFieldTester::AFlowFieldTester()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFlowFieldTester::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AFlowFieldTester::Setup, 0.5f, false);
}

void AFlowFieldTester::Setup()
{
	playerController = Cast<APlayerController>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerController::StaticClass()));

	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UMouseInteractionBase::StaticClass());
	if (FoundWidgets.Num() > 0)
		mouseInteraction = Cast<UMouseInteractionBase>(FoundWidgets[0]);

	hasSetup = mouseInteraction != nullptr && playerController != nullptr;
}

void AFlowFieldTester::CreateFlowField()
{
	flowField = MakeShared<FlowField>();
	flowField->Init(StartPoint, 50, FVector2i(30, 30), GetWorld(), WallCollision);
	flowFieldActive = true;
}

void AFlowFieldTester::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!hasSetup) return;
	
	const bool isLeftClickDownThisFrame = playerController->IsInputKeyDown(EKeys::LeftMouseButton);

	if (isLeftClickDownThisFrame && !mouseButtonDown && !flowFieldActive)
	{
		CreateFlowField();
		flowField->CreateCostField();

		const FVector mouseWorldPos = mouseInteraction->GetMousePosInWorld();
		const TSharedPtr<Cell> destinationCell = flowField->GetCellFromWorldPos(mouseWorldPos);

		if (destinationCell == nullptr)
		{
			flowField = nullptr;
			flowFieldActive = false;

			UE_LOG(LogTemp, Warning, TEXT("FlowField: Destination Cell is null"));
		}
		else
		{
			flowField->CreateIntegrationField(destinationCell);
			flowField->CreateFlowField();

			flowField->SetDebugType(FlowFieldDebugType::CostField);
			flowField->DrawDebug();	
		}
	}
	
	mouseButtonDown = isLeftClickDownThisFrame;

	if (flowFieldActive)
	{
		const bool clearButtonDownThisFrame = playerController->IsInputKeyDown(EKeys::C);
		if (clearButtonDownThisFrame && !clearDebugButtonDown)
		{
			flowField = nullptr;
			flowFieldActive = false;
			FlushDebugStrings(GetWorld());
			FlushPersistentDebugLines(GetWorld());
		}

		clearDebugButtonDown = clearButtonDownThisFrame;
		
		const bool switchDebugModeDownThisFrame = playerController->IsInputKeyDown(EKeys::L);
		if (switchDebugModeDownThisFrame && !switchDebugButtonDown)
		{
			if (flowField != nullptr)
			{
				if (flowField->debugType == FlowFieldDebugType::CostField)
					flowField->SetDebugType(FlowFieldDebugType::IntegrationField);
				else if (flowField->debugType == FlowFieldDebugType::IntegrationField)
					flowField->SetDebugType(FlowFieldDebugType::BestDirection);
				else 
					flowField->SetDebugType(FlowFieldDebugType::CostField);

				flowField->DrawDebug();	
			}
		}

		switchDebugButtonDown = switchDebugModeDownThisFrame;
	}
}
