#include "UnitManager.h"

#include "TowerDefense/UI/MouseInteractionBase.h"

AUnitManager::AUnitManager()
{

}

void AUnitManager::Setup(UHUDBase* _hud, TScriptInterface<IMouseInteractionInterface> _mouseInteraction, APlayerController* _playerController)
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
	pendingUnits = selectedUnits;
	mouseDownTime = FPlatformTime::Seconds();
}

TArray<FVector> AUnitManager::GenerateHoneycombDestinations(const FVector& center, int32 unitCount, float hexSize) const
{
	TArray<FVector> destinations;
	destinations.Add(center);  // First destination is the center

	int ring = 1;  // Start with the first ring
	while (destinations.Num() < unitCount)
	{
		const int unitsInThisRing = 6 * ring;
		const float angleIncrement = 2.0f * PI / unitsInThisRing;

		for (int i = 0; i < unitsInThisRing && destinations.Num() < unitCount; ++i)
		{
			const float angle = angleIncrement * i;
			const FVector offset = FVector(FMath::Cos(angle), FMath::Sin(angle), 0.0f) * hexSize * ring;
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
    if (clickTime < clickDeltaTime && hud->CurrentCommand != UnitCommand::None && pendingUnits.Num() > 0)
    {
        const FVector location = mouseInteraction->GetMousePosInWorld();
        TArray<FVector> destinations = GenerateHoneycombDestinations(location, pendingUnits.Num(), 250.0f);

    	DrawDebugSphere(GetWorld(), location, 10.0f, 12, FColor::Red, false, 2.0f);

        // Sort units based on their distance to the center location
    	pendingUnits.Sort([location](IUnit& A, IUnit& B) {
			const AActor* actorA = Cast<AActor>(&A);
			const AActor* actorB = Cast<AActor>(&B);
			return FVector::DistSquared(actorA->GetActorLocation(), location) < FVector::DistSquared(actorB->GetActorLocation(), location);
		});
    	
        for (IUnit* unit : pendingUnits)
        {
            const AActor* actor = Cast<AActor>(unit);
            const FVector currentUnitLocation = actor->GetActorLocation();

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
                const FVector furthestDestination = destinations[furthestIndex];
                unit->MoveToLocation(furthestDestination);
                destinations.RemoveAt(furthestIndex);  // Remove the assigned destination
            }
        }

    	pendingUnits.Empty();
    }
}