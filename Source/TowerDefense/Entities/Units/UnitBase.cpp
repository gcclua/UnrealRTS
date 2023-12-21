#include "UnitBase.h"

#include "AIController.h"
#include "NavigationSystem.h"

AUnitBase::AUnitBase()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
}

void AUnitBase::MoveToLocation(FVector _location)
{
	destination = _location;

	AAIController* AIController = Cast<AAIController>(GetController());
	
	if (AIController != nullptr)
	{
		float acceptanceRadius = 0;
		bool stopOnOverlap = true;
		bool usePathfinding = true;
		bool canStrafe = false;
		bool projectDestinationToNavigation = true;      
		TSubclassOf<UNavigationQueryFilter> filterClass = nullptr;
		bool allowPartialPath = true;
		
		AIController->MoveToLocation(destination, acceptanceRadius, stopOnOverlap,
									 usePathfinding, canStrafe,
							 projectDestinationToNavigation, filterClass, allowPartialPath);
	}
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
