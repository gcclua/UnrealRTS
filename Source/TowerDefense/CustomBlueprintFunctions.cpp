// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomBlueprintFunctions.h"

bool UCustomBlueprintFunctions::DoesImplementInterface(const TSubclassOf<AActor> actorClass, const TSubclassOf<UInterface> interface)
{
	return actorClass->ImplementsInterface(interface);
}
