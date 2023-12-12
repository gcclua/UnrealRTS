// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "TowerDefense/Enums/UnitCommand.h"
#include "HUDBase.generated.h"

UCLASS()
class TOWERDEFENSE_API UHUDBase : public UUserWidget
{
	GENERATED_BODY()

private:
	TWeakObjectPtr<APlayerController> playerController;

	void OnPressAttack();
	void OnPressWalk();
	void OnPressQ();
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* attackImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* walkImage;
	
	UnitCommand CurrentCommand;

	UFUNCTION(BlueprintCallable)
	void Setup(APlayerController* _playerController);
};
