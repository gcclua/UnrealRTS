#pragma once

#include "IBuilding.h"
#include "TowerDefense/Entities/BaseEntity.h"
#include "BuildingBase.generated.h"

UCLASS()
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildingBase")
	FString NameString;
	
	UFUNCTION(BlueprintCallable)
	void OnSpawn();

	UFUNCTION(BlueprintNativeEvent)
	void OnPlace();

	UFUNCTION(BlueprintCallable)
	void OnDoneConstructing();

	virtual bool IsMultiSelectable() override;

	// IBuilding
	virtual void UpgradeToLevel(int _level) override;
	virtual int CurrentLevel() override;
	virtual int MaxLevel() override;
	virtual int NextCostMoney() override;
	virtual FString HeaderString() override;

protected:
	int level;
};
