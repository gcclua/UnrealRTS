#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerDefense/Entities/Builder/BuilderBase.h"
#include "TowerDefense/Entities/Buildings/BuildingBase.h"
#include "BuilderManager.generated.h"

UCLASS()
class ABuilderManager : public AActor
{
	GENERATED_BODY()

private:
	TQueue<ABuildingBase*> buildingQueue;
	
	bool TrySendOutBuilder();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuilderManager")
	int NumBuilders;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuilderManager")
	FVector BuilderSpawnOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuilderManager")
	TSubclassOf<ABuilderBase> BuilderClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuilderManager")
	TArray<ABuilderBase*> Builders;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuilderManager")
	AActor* SpawnTransform;
	
public:
	UFUNCTION(BlueprintCallable)
	bool RequestBuilder(ABuildingBase* building);

	UFUNCTION(BlueprintCallable)
	void OnCompleteBuild(ABuilderBase* builder);

protected:
	virtual void BeginPlay() override;
};
