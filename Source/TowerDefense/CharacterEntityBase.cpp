// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEntityBase.h"

// Sets default values
ACharacterEntityBase::ACharacterEntityBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterEntityBase::BeginPlay()
{
	Super::BeginPlay();

	auto minimap = Cast<UMiniMap>(UGameplayStatics::GetActorOfClass(GetWorld(), UMiniMap::StaticClass()));
	minimap->RegisterEntity(this);
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

