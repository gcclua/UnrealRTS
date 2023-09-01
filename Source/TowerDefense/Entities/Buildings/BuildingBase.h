#pragma once

#include "TowerDefense/Entities/BaseEntity.h"
#include "BuildingBase.generated.h"

UCLASS(ABSTRACT)
class ABuildingBase : public ABaseEntity
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BuildTime = 3;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsConstruction = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABuildingBase> RealBuildingClass;
	
	UFUNCTION(BlueprintCallable)
	void OnSpawn();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlace();

	UFUNCTION(BlueprintCallable)
	void OnDoneConstructing();

	virtual bool IsSelectable() override;
};
