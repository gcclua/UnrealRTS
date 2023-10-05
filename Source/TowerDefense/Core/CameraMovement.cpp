// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraMovement.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "TowerDefense/UI/MouseInteractionBase.h"

ACameraMovement::ACameraMovement()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	PrimaryActorTick.bCanEverTick = true;
}

void ACameraMovement::Setup(UInputComponent* _inputComponent, UMouseInteractionBase* _mouseInteraction)
{
	_inputComponent->BindKey(EKeys::RightMouseButton, IE_Pressed, this, &ACameraMovement::OnRightClick);
	_inputComponent->BindKey(EKeys::RightMouseButton, IE_Released, this, &ACameraMovement::ReleaseRightClick);
	_inputComponent->BindKey(EKeys::W, IE_Pressed, this, &ACameraMovement::OnPanUp);
	_inputComponent->BindKey(EKeys::A, IE_Pressed, this, &ACameraMovement::OnPanLeft);
	_inputComponent->BindKey(EKeys::S, IE_Pressed, this, &ACameraMovement::OnPanDown);
	_inputComponent->BindKey(EKeys::D, IE_Pressed, this, &ACameraMovement::OnPanRight);
	_inputComponent->BindKey(EKeys::W, IE_Released, this, &ACameraMovement::ReleasePanUp);
	_inputComponent->BindKey(EKeys::A, IE_Released, this, &ACameraMovement::ReleasePanLeft);
	_inputComponent->BindKey(EKeys::S, IE_Released, this, &ACameraMovement::ReleasePanDown);
	_inputComponent->BindKey(EKeys::D, IE_Released, this, &ACameraMovement::ReleasePanRight);
	_inputComponent->BindAxis("ScrollWheel", this, &ACameraMovement::OnScroll);

	mouseInteraction = _mouseInteraction;

	curPos = GetActorLocation();
	keyboardMovement = FVector2d(0, 0);
}

void ACameraMovement::BeginPlay()
{
	Super::BeginPlay();

	curZoom = SpringArm->TargetArmLength;
}

void ACameraMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (holdingRightClick)
	{
		const FVector worldPos = mouseInteraction->GetMousePosInWorld();
		const FVector2d curMousePos = FVector2d(worldPos.X, worldPos.Y);

		FVector2d curPos2d = FVector2d(curPos.X, curPos.Y);
		const FVector2d mouseOffsetCurFrame = curMousePos - curPos2d;

		curPos2d = startMouseHoldPos - mouseOffsetCurFrame;
		
		curPos.X = curPos2d.X;
		curPos.Y = curPos2d.Y;

		SetActorLocation(curPos);
		return;
	}

	if (keyboardMovement.X != 0 || keyboardMovement.Y != 0)
	{
		const FVector movementDelta = FVector(keyboardMovement.X * DeltaTime, keyboardMovement.Y * DeltaTime, 0);
		curPos += movementDelta;
		SetActorLocation(curPos);

		if (flicking)
			flicking = false;
		return;
	}
	
	if (flicking)
	{
		

		//UE_LOG(LogTemp, Warning, TEXT("%s"), *curMousePos.ToString());
	}
}

#pragma region input binding crap

#pragma region press

void ACameraMovement::OnRightClick()
{
	const FVector worldPos = mouseInteraction->GetMousePosInWorld();
	startMouseHoldPos = FVector2d(worldPos.X, worldPos.Y);
	
	holdingRightClick = true;
	flicking = false;
}

void ACameraMovement::OnPanUp()
{
	keyboardMovement += FVector2d(0, keyboardScrollSpeed);
}

void ACameraMovement::OnPanDown()
{
	keyboardMovement -= FVector2d(0, keyboardScrollSpeed);
}

void ACameraMovement::OnPanLeft()
{
	keyboardMovement += FVector2d(keyboardScrollSpeed, 0);
}

void ACameraMovement::OnPanRight()
{
	keyboardMovement -= FVector2d(keyboardScrollSpeed, 0);
}

#pragma endregion

#pragma region release

void ACameraMovement::ReleaseRightClick()
{
	holdingRightClick = false;
	flicking = true;
	// get initial speed etc
}

void ACameraMovement::ReleasePanUp()
{
	keyboardMovement -= FVector2d(0, keyboardScrollSpeed);
}

void ACameraMovement::ReleasePanDown()
{
	keyboardMovement += FVector2d(0, keyboardScrollSpeed);
}

void ACameraMovement::ReleasePanLeft()
{
	keyboardMovement -= FVector2d(keyboardScrollSpeed, 0);
}

void ACameraMovement::ReleasePanRight()
{
	keyboardMovement += FVector2d(keyboardScrollSpeed, 0);
}

void ACameraMovement::OnScroll(float amt)
{
	if (amt == 0)
		return;

	curZoom = FMath::Clamp(curZoom + (amt * zoomSensitivity), minZoom, maxZoom);
	SpringArm->TargetArmLength = curZoom;
}

#pragma endregion 

#pragma endregion 

