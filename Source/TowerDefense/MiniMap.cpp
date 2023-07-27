// Fill out your copyright notice in the Description page of Project Settings.

#include "MiniMap.h"

void UMiniMap::OnUpdate()
{
}

void UMiniMap::RegisterEntity(IEntity* entity)
{
	AActor* actor = dynamic_cast<AActor*>(entity);

	auto location = actor->GetActorLocation();

	UE_LOG(LogTemp, Warning, TEXT("%s"), *location.ToString());
	UE_LOG(LogTemp, Warning, TEXT("%s"), *actor->GetHumanReadableName());
}

void UMiniMap::UnRegisterEntity(IEntity* entity)
{
}

bool UMiniMap::Initialize()
{
	Super::Initialize();

	return true;
}
