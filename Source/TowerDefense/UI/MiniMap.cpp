// Fill out your copyright notice in the Description page of Project Settings.

#include "MiniMap.h"

void UMiniMap::OnUpdate()
{
	if (!hasSetup || !centerActor)
		return;
	
	const double halfWidth = 200;
	const FVector2d center = FVector2d(-halfWidth, -halfWidth);
	
	FVector centerActorLocation = centerActor->GetActorLocation();
	centerActorLocation.SetComponentForAxis(EAxis::Z, 0);
	
	for (int i = 0; i < actors.Num(); i++)
	{
		const AActor* actor = actors[i];
		if (!actor || !markers[actor].slot)
			continue;

		const FWidgetSlot marker = markers[actor];
		UCanvasPanelSlot* iconSlot = marker.slot;
		UUserWidget* iconWidget = marker.widget;

		FVector actorPos = actor->GetActorLocation();
		actorPos.SetComponentForAxis(EAxis::Z, 0);

		const double distance = FVector::Distance(centerActorLocation, actorPos);
		if (distance > MinimapRadius)
		{
			iconWidget->SetVisibility(ESlateVisibility::Hidden);
			continue;
		}
		
		iconWidget->SetVisibility(ESlateVisibility::Visible);
		const double distance01 = UKismetMathLibrary::NormalizeToRange(distance, 0, MinimapRadius);
		FVector delta = actorPos - centerActorLocation;
		delta.Normalize();
		
		const FVector2d posDelta = (FVector2d(-delta.X, -delta.Y) * distance01 * halfWidth);
		const FVector2d pos = center + posDelta;
		iconSlot->SetPosition(pos);
	}
}

void UMiniMap::RegisterActor(AActor* actor)
{
	const auto iconWidget = CreateWidget<UUserWidget>(playerController, markerClass);
	if (!iconWidget)
		return;

	UCanvasPanelSlot* iconSlot = MinimapCanvas->AddChildToCanvas(iconWidget);
	
	FAnchors anchors = iconSlot->GetAnchors();
	anchors.Maximum = FVector2d(0, 0);
	anchors.Minimum = FVector2d(1, 1);
	iconSlot->SetAnchors(anchors);
	iconWidget->SetVisibility(ESlateVisibility::Hidden);

	actors.Add(actor);
	markers.Add(actor, FWidgetSlot(iconWidget, iconSlot));
}

void UMiniMap::UnRegisterActor(AActor* actor)
{
	const FWidgetSlot widgetSlot = markers[actor];
	widgetSlot.widget->RemoveFromParent();

	markers.Remove(actor);	
	actors.Remove(actor);
}

void UMiniMap::Setup(APlayerController* player, AActor* _centerActor)
{
	playerController = player;
	centerActor = _centerActor;
	hasSetup = true;
}

bool UMiniMap::Initialize()
{
	Super::Initialize();
	
	hasSetup = false;

	return true;
}
