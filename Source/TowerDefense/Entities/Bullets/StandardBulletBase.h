#pragma once

#include "CoreMinimal.h"
#include "BulletBase.h"
#include "StandardBulletBase.generated.h"

UCLASS(ABSTRACT)
class TOWERDEFENSE_API AStandardBulletBase : public ABulletBase
{
	GENERATED_BODY()

public:
	virtual void Fire(AActor* target) override;
};
