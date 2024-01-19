#pragma once

#include "IEntityManager.generated.h"

UINTERFACE(MinimalAPI)
class UEntityManagerInterface : public UInterface
{
	GENERATED_BODY()
};

class IEntityManagerInterface : public IInterface
{
	GENERATED_BODY()
	
public:
	virtual void UpdateSelectedEntitiesInRange(const FVector topLeft, const FVector bottomRight, const FVector bottomLeft, const FVector topRight) = 0;
	virtual void DeselectAllEntities() = 0;
};
