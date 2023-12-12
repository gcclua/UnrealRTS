// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDBase.h"

void UHUDBase::Setup(APlayerController* _playerController)
{
	playerController = _playerController;
	OnPressQ();

	_playerController->InputComponent->BindKey(EKeys::R, IE_Pressed, this, &UHUDBase::OnPressAttack);
	_playerController->InputComponent->BindKey(EKeys::E, IE_Pressed, this, &UHUDBase::OnPressWalk);
	_playerController->InputComponent->BindKey(EKeys::Q, IE_Pressed, this, &UHUDBase::OnPressQ);
}

void UHUDBase::OnPressAttack()
{
	if (CurrentCommand == UnitCommand::Attack)
	{
		OnPressQ();
		return;
	}

	if (CurrentCommand == UnitCommand::Walk)
		walkImage->SetVisibility(ESlateVisibility::Hidden);
	attackImage->SetVisibility(ESlateVisibility::Visible);
	CurrentCommand = UnitCommand::Attack;
}

void UHUDBase::OnPressWalk()
{
	if (CurrentCommand == UnitCommand::Walk)
	{
		OnPressQ();
		return;
	}
	
	if (CurrentCommand == UnitCommand::Attack)
		attackImage->SetVisibility(ESlateVisibility::Hidden);
	walkImage->SetVisibility(ESlateVisibility::Visible);
	CurrentCommand = UnitCommand::Walk;
}

void UHUDBase::OnPressQ()
{
	attackImage->SetVisibility(ESlateVisibility::Hidden);
	walkImage->SetVisibility(ESlateVisibility::Hidden);
	CurrentCommand = UnitCommand::None;
}
