// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "TowerDefense/Interfaces/IEntityManager.h"
#include "TowerDefense/Interfaces/IMouseInteraction.h"
#include "MouseInteractionBase.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UMouseInteractionBase : public UUserWidget, public IMouseInteractionInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MouseInteraction")
	TArray<TEnumAsByte<EObjectTypeQuery>> GroundCollision;
	
	UFUNCTION(BlueprintCallable)
	void Setup(APlayerController* _playerController, TScriptInterface<IEntityManagerInterface> _entityManager);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	USizeBox* SelectionBox;

	virtual void OnUpdate() override;

	virtual FVector GetMousePosInWorld() const override;
	FVector GetWorldPos(FVector2d screenPos) const;

private:
	UPROPERTY() APlayerController* playerController;
	UPROPERTY() UWorld* world;
	TScriptInterface<IEntityManagerInterface> entityManager;
	
	UPROPERTY() UCanvasPanelSlot* selectionBoxSlot;
	FVector2d startDragPos;
	FAnchors curDragAnchors;
	bool isDragging = false;

	FVector GetWorldPos(FVector2d screenPos, FVector2d scaleFactor) const;
};
