// Fill out your copyright notice in the Description page of Project Settings.

#include "MiniMap.h"
#include "Logger.h"

void UMiniMap::OnUpdate()
{
	if (!centerActor)
		return;
	
	const double halfWidth = 200;
	const FVector2d center = FVector2d(-halfWidth, -halfWidth);
	double maxDist = 2000;
	
	FVector centerActorLocation = centerActor->GetActorLocation();
	centerActorLocation.SetComponentForAxis(EAxis::Z, 0);
	
	for (int i = 0; i < actors.Num(); i++)
	{
		AActor* actor = actors[i];
		if (!actor || !markers[actor].slot)
			continue;
		
		UCanvasPanelSlot* iconSlot = markers[actor].slot;

		FVector actorPos = actor->GetActorLocation();
		actorPos.SetComponentForAxis(EAxis::Z, 0);
		
		FVector delta = actorPos - centerActorLocation;
		delta.Normalize();

		double distance = FVector::Distance(centerActorLocation, actorPos);
		double distance01 = UKismetMathLibrary::NormalizeToRange(distance, 0, maxDist);

		FVector2d posDelta = (FVector2d(delta.X, delta.Y) * distance01 * halfWidth);

		FVector2d pos = center + posDelta;
		iconSlot->SetPosition(pos);
	}
}

void UMiniMap::RegisterActor(AActor* actor)
{
	auto iconWidget = CreateWidget<UUserWidget>(playerController, markerClass);
	if (!iconWidget)
		return;

	UCanvasPanelSlot* iconSlot = MinimapCanvas->AddChildToCanvas(iconWidget);
	
	auto anchors = iconSlot->GetAnchors();
	anchors.Maximum = FVector2d(0, 0);
	anchors.Minimum = FVector2d(1, 1);
	iconSlot->SetAnchors(anchors);

	FVector2d center = FVector2d(-200, -200);
	iconSlot->SetPosition(center);

	actors.Add(actor);
	markers.Add(actor, FWidgetSlot(iconWidget, iconSlot));

	LOG_WARNING("RegisterActor");
}

void UMiniMap::UnRegisterActor(AActor* actor)
{
	auto widgetSlot = markers[actor];
	widgetSlot.widget->RemoveFromParent();

	markers.Remove(actor);	
	actors.Remove(actor);
	
	LOG_WARNING("Minimap Unregister");
}

void UMiniMap::Setup(APlayerController* player, AActor* _centerActor)
{
	playerController = player;
	centerActor = _centerActor;
	LOG_WARNING("Minimap Setup %s", *player->GetName());
}

bool UMiniMap::Initialize()
{
	Super::Initialize();

	LOG_WARNING("MINIMAP INIT");

	return true;
}
