// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDBase.h"

void UHUDBase::Setup(APlayerController* _playerController)
{
	playerController = _playerController;
	curCommand = UnitCommand::None;
	SetupSubPanels();
}

// quick and dirty, this can definitely be optimised
void UHUDBase::SetHUDPanelVisibility(HUDPanelType panelType, bool state)
{
	if (!hudPanelStates.Contains(panelType))
		return;

	hudPanelStates[panelType] = state;

	TWeakObjectPtr<UHUDPanelBase> highestPriorityPanel = nullptr;
	int highestPriority = INT_MIN;
	
	for (TWeakObjectPtr<UHUDPanelBase> panel : subPanelInstances)
	{
		if (!panel.IsValid())
			continue;
		
		if (hudPanelStates[panel->PanelType])
		{
			if (panel->PanelPriority > highestPriority)
			{
				highestPriority = panel->PanelPriority;
				highestPriorityPanel = panel;
			}
		}
	}

	for (TWeakObjectPtr<UHUDPanelBase> panel : subPanelInstances)
	{
		if (!panel.IsValid())
			continue;

		panel->SetVisibility(panel == highestPriorityPanel ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
}

void UHUDBase::SetupSubPanels()
{
	for (TSubclassOf<UHUDPanelBase> panelClass : HUDPanelClasses)
	{
		if (panelClass == nullptr)
			continue;
		
		UHUDPanelBase* panelWidget = CreateWidget<UHUDPanelBase>(this, panelClass);
		if (panelWidget == nullptr)
			continue;
		
		UCanvasPanelSlot* panelSlot = SubPanelCanvas->AddChildToCanvas(panelWidget);
		if (panelSlot == nullptr)
			continue;
		
		panelSlot->SetAnchors(FAnchors(0, 1, 0, 1));
		panelSlot->SetPosition(FVector2D(32, -32));
		panelSlot->SetAlignment(FVector2D(0, 1));
		panelWidget->SetVisibility(panelWidget->ShowOnStart ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
		panelWidget->Setup(this);
		
		subPanelInstances.Add(panelWidget);
		hudPanelStates.Add(panelWidget->PanelType, panelWidget->ShowOnStart);
	}
}

void UHUDBase::SetCommand(UnitCommand command)
{
	curCommand = command;
}

UObject* UHUDBase::GetPanel(HUDPanelType panelType)
{
	for (TWeakObjectPtr<UHUDPanelBase> panelInstance : subPanelInstances)
	{
		if (panelInstance.IsValid() && panelInstance->PanelType == panelType)
			return panelInstance.Get();
	}
	
	return nullptr;
}

UnitCommand UHUDBase::CurrentCommand()
{
	return curCommand;
}
