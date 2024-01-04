// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"

#include "MinimapEntityBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class TOWERDEFENSE_API UMinimapEntityBase : public UUserWidget
{
public:
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* Icon;
	
	void SetIconTexture(UTexture2D* newTexture);
};
