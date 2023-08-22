// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entities/Buildings/BuildingBase.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CustomBlueprintFunctions.generated.h"

UCLASS()
class TOWERDEFENSE_API UCustomBlueprintFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static bool DoesImplementInterface(TSubclassOf<AActor> actorClass, const TSubclassOf<UInterface> interface);
};
