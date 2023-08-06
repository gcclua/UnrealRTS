// Fill out your copyright notice in the Description page of Project Settings.

#include "ResourceFarmerBase.h"

AResourceFarmerBase::AResourceFarmerBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AResourceFarmerBase::BeginPlay()
{
	Super::BeginPlay();
}

void AResourceFarmerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
