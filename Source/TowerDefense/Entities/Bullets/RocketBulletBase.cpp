#include "RocketBulletBase.h"

void ARocketBulletBase::Fire(AActor* target)
{
	Super::Fire(target);

	ProjectileMovement->bIsHomingProjectile = true;

	USceneComponent* targetComponent = target->GetRootComponent();
	if (targetComponent != nullptr)
		ProjectileMovement->HomingTargetComponent = targetComponent;

	constexpr float destroyTime = 10;
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABulletBase::DestroyBullet, destroyTime, false);
}
