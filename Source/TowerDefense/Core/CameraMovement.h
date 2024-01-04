// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"
#include "TowerDefense/UI/MouseInteractionBase.h"
#include "CameraMovement.generated.h"

UCLASS()
class TOWERDEFENSE_API ACameraMovement : public AActor
{
	GENERATED_BODY()

private:
	void OnRightClick();
	void OnPanUp();
	void OnPanDown();
	void OnPanLeft();
	void OnPanRight();

	void ReleaseRightClick();
	void ReleasePanUp();
	void ReleasePanDown();
	void ReleasePanLeft();
	void ReleasePanRight();

	void OnScroll(float amt);
	
	FVector2d keyboardMovement;
	FVector2d startMouseHoldPos;
	FVector curPos;
	bool holdingRightClick;
	bool flicking;
	float curZoom;
	float flickVelocity;
	FVector2d prevMousePos;
	FVector2d flickDirection;
	
	UPROPERTY()
	UMouseInteractionBase* mouseInteraction;
	UPROPERTY()
	APlayerController* playerController;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMovement")
	float flickMaxInitialVelocity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMovement")
	float flickInitialVelocityMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMovement")
	float flickSlowdownRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMovement")
	float minZoom;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMovement")
	float maxZoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMovement")
	float zoomSensitivity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMovement")
	double keyboardScrollSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMovement")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMovement")
	FVector BoundsTopLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMovement")
	FVector BoundsBottomRight;

	UFUNCTION(BlueprintCallable)
	void Setup(APlayerController* _playerController, UMouseInteractionBase* _mouseInteraction);
	
	ACameraMovement();
	virtual void Tick(float DeltaTime) override;

	void ClampPosition(FVector& pos) const;
};
