#include "StandardBulletBase.h"

void AStandardBulletBase::Fire(AActor* target)
{
	Super::Fire(target);
	
	// destroy this bullet in the case that it doesnt hit anything
	if (target != nullptr && ProjectileMovement != nullptr)
	{
		constexpr float travelLeewayMultiplier = 1.2f;
		const float distance = (target->GetActorLocation() - GetActorLocation()).Size();
		const float travelTime = (distance / ProjectileMovement->InitialSpeed) * travelLeewayMultiplier;

		if (travelTime > 0)
		{
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABulletBase::DestroyBullet, travelTime, false);
		}
	}
}
