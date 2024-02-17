// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "HUDPanels/HUDPanelBase.h"
#include "TowerDefense/Interfaces/IHUD.h"
#include "HUDBase.generated.h"

UCLASS()
class TOWERDEFENSE_API UHUDBase : public UUserWidget, public IHUDInterface
{
	GENERATED_BODY()

private:
	TWeakObjectPtr<APlayerController> playerController;
	TArray<TWeakObjectPtr<UHUDPanelBase>> subPanelInstances;
	TMap<HUDPanelType, bool> hudPanelStates;

	UnitCommand curCommand;

	void SetupSubPanels();
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* SubPanelCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UHUDPanelBase>> HUDPanelClasses;

	UFUNCTION(BlueprintCallable)
	void Setup(APlayerController* _playerController);

	UFUNCTION(BlueprintCallable)
	void SetCommand(UnitCommand command);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMetal(int numMetal);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetStone(int numStone);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetWood(int numWood);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetHealth(float numHealth);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMoney(int numMoney);

	virtual UObject* GetPanel(HUDPanelType panelType) override;
	virtual UnitCommand CurrentCommand() override;
	virtual void SetHUDPanelVisibility(HUDPanelType panelType, bool state) override;
};
