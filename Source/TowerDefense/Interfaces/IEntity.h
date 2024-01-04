#pragma once
#include "TowerDefense/Enums/EntityType.h"

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
	virtual bool IsSelectable()
	{
		return false;
	}

	UFUNCTION()
	virtual EntityType GetEntityType()
	{
		return EntityType::None;
	}

	UFUNCTION(BlueprintImplementableEvent)
	UStaticMeshComponent* GetSelectionMesh();

	UFUNCTION(BlueprintImplementableEvent)
	UTexture2D* GetIcon();
};
