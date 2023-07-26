// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEntity.generated.h"

UCLASS()
class TOWERDEFENSE_API ABaseEntity : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseEntity();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInit();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnUpdate();

	UFUNCTION(BlueprintCallable, BlueprintCallable)
	void OnDestroy();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;

protected:
	virtual void BeginPlay() override;
};
