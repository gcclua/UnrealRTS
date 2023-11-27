#pragma once

#include "BaseEntity.h"
#include "BulletBase.generated.h"

UCLASS()
class TOWERDEFENSE_API ABulletBase : public ABaseEntity
{
	GENERATED_BODY()
	
public:
	ABulletBase();

	virtual EntityType GetEntityType() override;
};
