// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "MouseInteractionBase.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UMouseInteractionBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Setup(APlayerController* _playerController);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	USizeBox* SelectionBox;

	void OnUpdate();

private:
	UPROPERTY()
	APlayerController* playerController;

	UPROPERTY() UCanvasPanelSlot* selectionBoxSlot;
	FVector2d startDragPos;
	FAnchors curDragAnchors;
	bool isDragging = false;
};
