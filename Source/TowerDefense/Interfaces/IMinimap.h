#pragma once

#include "IUpdatable.h"
#include "IMinimap.generated.h"

UINTERFACE(MinimalAPI)
class UMinimapInterface : public UInterface
{
	GENERATED_BODY()
};

class IMinimapInterface : public IUpdatable
{
	GENERATED_BODY()
	
public:
	virtual void RegisterActor(AActor* actor, UTexture2D* texture) = 0;
	virtual void UnRegisterActor(AActor* actor) = 0;
};
