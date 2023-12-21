#pragma once

#include "IUnit.h"
#include "UnitState.h"
#include "TowerDefense/Entities/CharacterEntityBase.h"
#include "TowerDefense/Pathfinding/FlowField.h"
#include "UnitBase.generated.h"

UCLASS()
class TOWERDEFENSE_API AUnitBase : public ACharacterEntityBase, public IUnit
{
	GENERATED_BODY()

private:
	AUnitBase();

	UnitState state;
	FVector destination;

public:
	UPROPERTY(BlueprintReadOnly)
	USceneComponent* SceneComponent;
	
	virtual void MoveToLocation(FVector _location) override; 

	virtual bool IsSelectable() override;

	virtual EntityType GetEntityType() override;

	virtual UCharacterMovementComponent* GetCharMovement() override;
	virtual void Tick(float DeltaTime) override;
};
