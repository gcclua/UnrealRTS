// Fill out your copyright notice in the Description page of Project Settings.

#include "MiniMap.h"
#include "Logger.h"


void UMiniMap::OnUpdate()
{
	
}

void UMiniMap::DoShit_Implementation(int input)
{

}

void UMiniMap::SpawnMarker_Implementation(AActor* actor)
{

}

void UMiniMap::RegisterActor(AActor* actor)
{
	auto widget = CreateWidget<UUserWidget>(playerController, markerClass);
	if (!widget)
		return;
	
	widget->AddToViewport();
	widget->SetPositionInViewport(FVector2d(markers.Num() * 100, 100));
	actors.Add(actor);
	markers.Add(actor, widget);
}

void UMiniMap::UnRegisterActor(AActor* actor)
{
	LOG_WARNING("Minimap Unregister");
}

void UMiniMap::Setup(APlayerController* player)
{
	playerController = player;
	LOG_WARNING("Minimap Setup %s", *player->GetName());
}

bool UMiniMap::Initialize()
{
	Super::Initialize();

	LOG_WARNING("MINIMAP INIT");

	return true;
}
