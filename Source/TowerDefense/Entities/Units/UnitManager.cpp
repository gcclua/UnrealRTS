#include "UnitManager.h"

#include "TowerDefense/UI/MouseInteractionBase.h"

AUnitManager::AUnitManager()
{

}

void AUnitManager::Setup(UHUDBase* _hud, UMouseInteractionBase* _mouseInteraction, APlayerController* _playerController)
{
	hud = _hud;
	mouseInteraction = _mouseInteraction;

	_playerController->InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &AUnitManager::OnLeftClickDown);
	_playerController->InputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &AUnitManager::OnLeftClickUp);
}

void AUnitManager::AddCurrentlySelectedUnit(IUnit* _unit)
{
	if (!selectedUnits.Contains(_unit))
		selectedUnits.Add(_unit);
}

void AUnitManager::RemoveCurrentlySelectedUnit(IUnit* _unit)
{
	if (selectedUnits.Contains(_unit))
		selectedUnits.Remove(_unit);
}

void AUnitManager::OnLeftClickDown()
{
	mouseDownTime = FPlatformTime::Seconds();
}

TArray<FVector> AUnitManager::GenerateHoneycombDestinations(const FVector& center, int32 unitCount, float hexSize)
{
	TArray<FVector> destinations;
	destinations.Add(center);  // First destination is the center

	int ring = 1;  // Start with the first ring
	while (destinations.Num() < unitCount)
	{
		int unitsInThisRing = 6 * ring;
		float angleIncrement = 2.0f * PI / unitsInThisRing;

		for (int i = 0; i < unitsInThisRing && destinations.Num() < unitCount; ++i)
		{
			float angle = angleIncrement * i;
			FVector offset = FVector(FMath::Cos(angle), FMath::Sin(angle), 0.0f) * hexSize * ring;
			destinations.Add(center + offset);
		}

		ring++;
	}

	return destinations;
}

void AUnitManager::OnLeftClickUp()
{
    constexpr double clickDeltaTime = 0.2;
    const double curTime = FPlatformTime::Seconds();

    const float clickTime = curTime - mouseDownTime;
    if (clickTime < clickDeltaTime && hud->CurrentCommand != UnitCommand::None && selectedUnits.Num() > 0)
    {
        const FVector location = mouseInteraction->GetMousePosInWorld(true);
        TArray<FVector> destinations = GenerateHoneycombDestinations(location, selectedUnits.Num(), 250.0f);

        // Sort units based on their distance to the center location
    	selectedUnits.Sort([location](IUnit& A, IUnit& B) {
			AActor* actorA = Cast<AActor>(&A);
			AActor* actorB = Cast<AActor>(&B);
			return FVector::DistSquared(actorA->GetActorLocation(), location) < FVector::DistSquared(actorB->GetActorLocation(), location);
		});
    	
        for (IUnit* unit : selectedUnits)
        {
            AActor* actor = Cast<AActor>(unit);
            FVector currentUnitLocation = actor->GetActorLocation();

            // Find the furthest destination from the current unit's position
            int32 furthestIndex = -1;
            float maxDistance = 0.0f;
            for (int32 i = 0; i < destinations.Num(); ++i)
            {
                const float distance = FVector::DistSquared(currentUnitLocation, destinations[i]);
                if (distance > maxDistance)
                {
                    maxDistance = distance;
                    furthestIndex = i;
                }
            }

            if (furthestIndex != -1)
            {
                // Assign the unit to this destination
                FVector furthestDestination = destinations[furthestIndex];
                unit->MoveToLocation(furthestDestination);
                destinations.RemoveAt(furthestIndex);  // Remove the assigned destination

                // Debug drawing
                DrawDebugSphere(GetWorld(), furthestDestination, 10.0f, 12, FColor::Red, false, 5.0f);
            }
        }
    }
}