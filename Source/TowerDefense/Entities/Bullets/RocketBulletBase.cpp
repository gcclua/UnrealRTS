#include "RocketBulletBase.h"

void ARocketBulletBase::Fire(AActor* target, float _damage)
{
	Super::Fire(target, _damage);

	ProjectileMovement->bIsHomingProjectile = true;

	USceneComponent* targetComponent = target->GetRootComponent();
	if (targetComponent != nullptr)
		ProjectileMovement->HomingTargetComponent = targetComponent;

	constexpr float destroyTime = 10;
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABulletBase::DestroyBullet, destroyTime, false);
}
