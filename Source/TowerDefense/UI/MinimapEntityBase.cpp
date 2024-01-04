// Fill out your copyright notice in the Description page of Project Settings.

#include "MinimapEntityBase.h"

void UMinimapEntityBase::SetIconTexture(UTexture2D* newTexture)
{
	if (Icon != nullptr && newTexture != nullptr)
		Icon->SetBrushFromTexture(newTexture);
}
