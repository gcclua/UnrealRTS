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

void ACameraMovement::BeginPlay()
{
	Super::BeginPlay();
}

void ACameraMovement::Setup(APlayerController* _playerController, UMouseInteractionBase* _mouseInteraction)
{
	_playerController->InputComponent->BindKey(EKeys::RightMouseButton, IE_Pressed, this, &ACameraMovement::OnRightClick);
	_playerController->InputComponent->BindKey(EKeys::RightMouseButton, IE_Released, this, &ACameraMovement::ReleaseRightClick);
	_playerController->InputComponent->BindKey(EKeys::W, IE_Pressed, this, &ACameraMovement::OnPanUp);
	_playerController->InputComponent->BindKey(EKeys::A, IE_Pressed, this, &ACameraMovement::OnPanLeft);
	_playerController->InputComponent->BindKey(EKeys::S, IE_Pressed, this, &ACameraMovement::OnPanDown);
	_playerController->InputComponent->BindKey(EKeys::D, IE_Pressed, this, &ACameraMovement::OnPanRight);
	_playerController->InputComponent->BindKey(EKeys::W, IE_Released, this, &ACameraMovement::ReleasePanUp);
	_playerController->InputComponent->BindKey(EKeys::A, IE_Released, this, &ACameraMovement::ReleasePanLeft);
	_playerController->InputComponent->BindKey(EKeys::S, IE_Released, this, &ACameraMovement::ReleasePanDown);
	_playerController->InputComponent->BindKey(EKeys::D, IE_Released, this, &ACameraMovement::ReleasePanRight);
	_playerController->InputComponent->BindAxis("ScrollWheel", this, &ACameraMovement::OnScroll);

	mouseInteraction = _mouseInteraction;
	playerController = _playerController;

	curPos = GetActorLocation();
	curZoom = SpringArm->TargetArmLength;
	keyboardMovement = FVector2d(0, 0);
}

void ACameraMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector worldPos = mouseInteraction->GetMousePosInWorld();
	const FVector2d curMousePos = FVector2d(worldPos.X, worldPos.Y);
	
	if (holdingRightClick)
	{
		FVector2d curPos2d = FVector2d(curPos.X, curPos.Y);
		const FVector2d mouseOffsetCurFrame = curMousePos - curPos2d;

		curPos2d = startMouseHoldPos - mouseOffsetCurFrame;
		
		curPos.X = curPos2d.X;
		curPos.Y = curPos2d.Y;

		ClampPosition(curPos);
		SetActorLocation(curPos);
		return;
	}

	if (keyboardMovement.X != 0 || keyboardMovement.Y != 0)
	{
		const FVector movementDelta = FVector(keyboardMovement.X * DeltaTime, keyboardMovement.Y * DeltaTime, 0);
		curPos += movementDelta;
		
		ClampPosition(curPos);
		SetActorLocation(curPos);

		if (flicking)
			flicking = false;
		return;
	}
	
	if (flicking)
	{
		const float velocityCurFrame = flickVelocity * DeltaTime;
		const FVector2d delta = FVector2d (flickDirection.X * velocityCurFrame, flickDirection.Y * velocityCurFrame);
		const FVector nextPos = FVector(curPos.X + delta.X, curPos.Y + delta.Y, curPos.Z);
		
		curPos = nextPos;

		ClampPosition(curPos);
		SetActorLocation(curPos);

		flickVelocity -= flickSlowdownRate * DeltaTime;
		if (flickVelocity <= 0)
			flicking = false;
	}

	prevMousePos = curMousePos;
}

void ACameraMovement::ClampPosition(FVector& pos) const
{
	if (pos.X > BoundsTopLeft.X)
		pos.X = BoundsTopLeft.X;
	else if (pos.X < BoundsBottomRight.X)
		pos.X = BoundsBottomRight.X;

	if (pos.Y > BoundsTopLeft.Y)
		pos.Y = BoundsTopLeft.Y;
	else if (pos.Y< BoundsBottomRight.Y)
		pos.Y = BoundsBottomRight.Y;
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
	const FVector worldPos = mouseInteraction->GetMousePosInWorld();
	const FVector2d curMousePos = FVector2d(worldPos.X, worldPos.Y);
	
	flickDirection = prevMousePos - curMousePos;
	flickVelocity = FMath::Clamp(flickDirection.Length() * flickInitialVelocityMultiplier, 0, flickMaxInitialVelocity);
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

