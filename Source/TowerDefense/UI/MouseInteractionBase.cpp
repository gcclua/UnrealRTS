// Fill out your copyright notice in the Description page of Project Settings.

#include "MouseInteractionBase.h"

#include "Blueprint/WidgetLayoutLibrary.h"

void UMouseInteractionBase::Setup(APlayerController* _playerController)
{
	playerController = _playerController;
	selectionBoxSlot = Cast<UCanvasPanelSlot>(SelectionBox->Slot);
}

void UMouseInteractionBase::OnUpdate()
{
	const bool isLeftClickDown = playerController->IsInputKeyDown(EKeys::LeftMouseButton);
	const FVector2d mousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

	if (isDragging)
	{
		if (!isLeftClickDown)
		{
			isDragging = false;
			SelectionBox->SetVisibility(ESlateVisibility::Hidden);

			// deselect everything
			return;
		}

		FVector2d topLeft = mousePos;
		if (startDragPos.X < topLeft.X)
			topLeft.X = startDragPos.X;
		if (startDragPos.Y < topLeft.Y)
			topLeft.Y = startDragPos.Y;

		FVector2d posDelta = mousePos - startDragPos;
		posDelta.X = abs(posDelta.X);
		posDelta.Y = abs(posDelta.Y);

		selectionBoxSlot->SetPosition(topLeft);
		selectionBoxSlot->SetSize(posDelta);
		
		// update whats selected
	}
	else if (isLeftClickDown)
	{
		startDragPos = mousePos;
		
		selectionBoxSlot->SetPosition(startDragPos);
		
		SelectionBox->SetVisibility(ESlateVisibility::Visible);
		selectionBoxSlot->SetSize(FVector2d(0, 0));
		curDragAnchors = selectionBoxSlot->GetAnchors();

		isDragging = true;
	}
}
