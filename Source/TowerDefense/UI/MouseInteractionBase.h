// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "TowerDefense/Systems/EntityManager.h"
#include "MouseInteractionBase.generated.h"

class AEntityManager;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UMouseInteractionBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TEnumAsByte<EObjectTypeQuery>> GroundCollision;
	
	UFUNCTION(BlueprintCallable)
	void Setup(APlayerController* _playerController, AEntityManager* _entityManager);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	USizeBox* SelectionBox;

	void OnUpdate();

	FVector GetMousePosInWorld();
	FVector GetWorldPos(FVector2d screenPos);

private:
	UPROPERTY()
	APlayerController* playerController;
	UPROPERTY()
	AEntityManager* entityManager;
	UPROPERTY()
	UWorld* world;
	
	UPROPERTY() UCanvasPanelSlot* selectionBoxSlot;
	FVector2d startDragPos;
	FAnchors curDragAnchors;
	bool isDragging = false;

	FVector GetWorldPos(FVector2d screenPos, FVector2d scaleFactor);
};
