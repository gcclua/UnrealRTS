// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IEntity.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "MiniMap.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class TOWERDEFENSE_API UMiniMap : public UUserWidget
{
	GENERATED_BODY()

public: // variables/properties
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* minimapContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> markerClass;
	
	UPROPERTY() TArray<AActor*> actors;
	UPROPERTY()	TMap<AActor*, UUserWidget*> markers;
	UPROPERTY() APlayerController* playerController;
	
public: // methods
	UFUNCTION(BlueprintCallable)
	void OnUpdate();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SpawnMarker(AActor* actor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DoShit(int input);
	
	void RegisterActor(AActor* actor);
	void UnRegisterActor(AActor* actor);
	
	virtual void Setup(APlayerController* player);
	
	virtual bool Initialize() override;
};
