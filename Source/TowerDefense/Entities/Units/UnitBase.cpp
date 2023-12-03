#include "UnitBase.h"

AUnitBase::AUnitBase()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
}

void AUnitBase::MoveToDestination(TSharedPtr<FlowField> _flowField, FVector _destination)
{
	flowField = _flowField;
	destination = _destination;

	
}

bool AUnitBase::IsSelectable()
{
	return true;
}

EntityType AUnitBase::GetEntityType()
{
	return EntityType::Unit;
}

UCharacterMovementComponent* AUnitBase::GetCharMovement()
{
	return GetCharacterMovement();
}

void AUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (state == UnitState::WalkingToDestination)
	{
		
	}
}
