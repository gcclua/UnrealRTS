#pragma once

#include "IBuilding.h"
#include "TowerDefense/Entities/BaseEntity.h"
#include "BuildingBase.generated.h"

UCLASS(ABSTRACT)
class ABuildingBase : public ABaseEntity, public IBuilding
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildingBase")
	float BuildTime = 3;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildingBase")
	bool IsConstruction = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildingBase")
	TSubclassOf<ABuildingBase> RealBuildingClass;
	
	UFUNCTION(BlueprintCallable)
	void OnSpawn();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlace();

	UFUNCTION(BlueprintCallable)
	void OnDoneConstructing();

	virtual bool IsMultiSelectable() override;
};
