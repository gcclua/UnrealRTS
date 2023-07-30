// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterEntityBase.h"

// Sets default values
ACharacterEntityBase::ACharacterEntityBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACharacterEntityBase::Register()
{
	auto entityManager = Cast<AEntityManager>(UGameplayStatics::GetActorOfClass(GetWorld(), UMiniMap::StaticClass()));
	entityManager->RegisterEntity(this);
}

// Called when the game starts or when spawned
void ACharacterEntityBase::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ACharacterEntityBase::Register, 0.5f, false);
}

// Called every frame
void ACharacterEntityBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterEntityBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

