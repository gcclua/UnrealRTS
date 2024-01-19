// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MinimapEntityBase.h"
#include "../Interfaces/IEntity.h"
#include "WidgetSlot.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/KismetMathLibrary.h"
#include "TowerDefense/Interfaces/IMinimap.h"
#include "MiniMap.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class TOWERDEFENSE_API UMiniMap : public UUserWidget, public IMinimapInterface
{
	GENERATED_BODY()

private:
	UPROPERTY() AActor* centerActor;

public: // variables/properties
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCanvasPanel* MinimapCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UMinimapEntityBase> markerClass;

	UPROPERTY(EditAnywhere)
	float MinimapRadius;

	bool hasSetup = false;
	
	UPROPERTY() TArray<AActor*> actors;
	UPROPERTY()	TMap<AActor*, FWidgetSlot> markers;
	UPROPERTY() APlayerController* playerController;
	
public: // methods
	virtual void OnUpdate() override;
	
	virtual void RegisterActor(AActor* actor, UTexture2D* texture) override;
	virtual void UnRegisterActor(AActor* actor) override;

	UFUNCTION(BlueprintCallable)
	void Setup(APlayerController* player, AActor* _centerActor);
	
	virtual bool Initialize() override;
};
