#pragma once

#include "BuilderState.h"
#include "TowerDefense/Entities/CharacterEntityBase.h"
#include "TowerDefense/Entities/Buildings/BuildingBase.h"
#include "BuilderBase.generated.h"

UCLASS()
class TOWERDEFENSE_API ABuilderBase : public ACharacterEntityBase
{
    GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	BuilderState CurrentState = BuilderState::Idle;
	
	UPROPERTY(BlueprintReadWrite)
	ABuildingBase* CurrentBuilding;
	
public:
	bool IsBusy() const;
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnStartJob(ABuildingBase* building);

	virtual EntityType GetEntityType() override;
};
