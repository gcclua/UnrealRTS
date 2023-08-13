#pragma once

#include "TowerDefense/Entities/BaseEntity.h"
#include "BuildingBase.generated.h"

UCLASS(ABSTRACT)
class ABuildingBase : public ABaseEntity
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnPlace();
};
