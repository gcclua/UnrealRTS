#pragma once

#include "IEntity.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UEntity : public UInterface
{
	GENERATED_BODY()
};

class IEntity : public IInterface
{
	GENERATED_BODY()

public:

	UFUNCTION()
	virtual AActor* GetActor();
};