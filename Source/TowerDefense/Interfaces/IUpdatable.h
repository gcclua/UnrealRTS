#pragma once

#include "IUpdatable.generated.h"

UINTERFACE(MinimalAPI)
class UUpdatable : public UInterface
{
	GENERATED_BODY()
};

class IUpdatable : public IInterface
{
	GENERATED_BODY()
	
public:
	virtual void OnUpdate() = 0;
};
