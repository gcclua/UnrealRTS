#pragma once

#include "CoreMinimal.h"
#include "BulletBase.h"
#include "RocketBulletBase.generated.h"

UCLASS()
class TOWERDEFENSE_API ARocketBulletBase : public ABulletBase
{
	GENERATED_BODY()

public:
	virtual void Fire(AActor* target) override;
};
