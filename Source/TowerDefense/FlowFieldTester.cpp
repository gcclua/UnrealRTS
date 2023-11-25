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
	flowField->Init(50, FVector2i(30, 30), GetWorld(), WallCollision);
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
		
		flowField->CreateIntegrationField(destinationCell);

		flowField->SetDebugType(FlowFieldDebugType::CostField);
		flowField->DrawDebug();
	}
	
	mouseButtonDown = isLeftClickDownThisFrame;

	if (flowFieldActive)
	{
		const bool switchDebugModeDownThisFrame = playerController->IsInputKeyDown(EKeys::L);
		if (switchDebugModeDownThisFrame && !switchDebugButtonDown)
		{
			if (flowField->debugType == FlowFieldDebugType::CostField)
				flowField->SetDebugType(FlowFieldDebugType::IntegrationField);
			else
				flowField->SetDebugType(FlowFieldDebugType::CostField);

			flowField->DrawDebug();
		}

		switchDebugButtonDown = switchDebugModeDownThisFrame;
	}
}

