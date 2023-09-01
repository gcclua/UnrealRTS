#pragma once

#include "TowerDefense/Entities/CharacterEntityBase.h"
#include "EnemyBase.generated.h"

UCLASS()
class TOWERDEFENSE_API AEnemyBase : public ACharacterEntityBase
{
	GENERATED_BODY()

private:
	AEnemyBase();

public:
	UPROPERTY(BlueprintReadOnly)
	USceneComponent* SceneComponent;

	virtual bool IsSelectable() override;
};
