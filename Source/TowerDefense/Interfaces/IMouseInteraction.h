#pragma once

#include "IUpdatable.h"
#include "IMouseInteraction.generated.h"

UINTERFACE(MinimalAPI)
class UMouseInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class IMouseInteractionInterface : public IUpdatable
{
	GENERATED_BODY()
	
public:
	virtual FVector GetMousePosInWorld() const = 0;
};
