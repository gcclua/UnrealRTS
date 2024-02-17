// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerVitalsBase.h"

APlayerVitalsBase* APlayerVitalsBase::Instance = nullptr;

APlayerVitalsBase::APlayerVitalsBase()
{
	myInputComponent = nullptr;
	Health = 0;
	Stone = 0;
	Wood = 0;
	Metal = 0;
	Money = 0;
	PrimaryActorTick.bCanEverTick = true;
}

APlayerVitalsBase* APlayerVitalsBase::GetInstance()
{
	return Instance;
}

void APlayerVitalsBase::BeginPlay()
{
	Instance = this;
	Super::BeginPlay();
}

void APlayerVitalsBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerVitalsBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	myInputComponent = PlayerInputComponent;
}

int APlayerVitalsBase::GetMoney() const
{
	return Money;
}

void APlayerVitalsBase::SetMoney(int newMoney)
{
	Money = newMoney;
	HUD->SetMoney(Money);
}

void APlayerVitalsBase::AddMoney(int amount)
{
	SetMoney(Money + amount);
}

void APlayerVitalsBase::OnEnemyReachEnd_Implementation(AActor* enemyActor, EnemyType enemyType, double damage) { }
void APlayerVitalsBase::OnGatherResource_Implementation(ResourceType resource, int amount) { }
