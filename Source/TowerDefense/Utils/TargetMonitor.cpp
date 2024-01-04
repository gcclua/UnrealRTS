#include "TargetMonitor.h"

TargetMonitor::TargetMonitor(AActor* _attachedActor)
{
	attachedActor = _attachedActor;
}

void TargetMonitor::OnOverlapBegin(AActor* other)
{
	AEnemyBase* enemy = Cast<AEnemyBase>(other);
	if (enemy)
	{
		const FGuid guid = enemy->GetActorGuid();

		if (targetsInRange.Contains(guid))
			return;
		
		targetsInRange.Add(guid, enemy);
		hasTargetInRange = true;

		if (!currentTarget.IsValid())
		{
			currentTarget = enemy;
			HasTarget = true;
		}
	}
}

void TargetMonitor::OnOverlapEnd(AActor* other)
{
	AEnemyBase* enemy = Cast<AEnemyBase>(other);
	if (enemy)
	{
		const FGuid guid = enemy->GetActorGuid();

		if (!targetsInRange.Contains(guid))
			return;
		
		targetsInRange.Remove(guid);
		hasTargetInRange = targetsInRange.Num() > 0;

		if (currentTarget == enemy || !currentTarget.IsValid())
		{
			RecalculateTarget();
		}
	}
}

AEnemyBase* TargetMonitor::GetTarget() const
{
	return currentTarget.Get();
}

void TargetMonitor::RecalculateTarget()
{
	if (hasTargetInRange)
	{
		currentTarget = FindClosestTarget(attachedActor->GetActorLocation());
		HasTarget = currentTarget.IsValid();
	}
	else
	{
		currentTarget = nullptr;
		HasTarget = false;
	}
}

TWeakObjectPtr<AEnemyBase> TargetMonitor::FindClosestTarget(const FVector& position)
{
	TWeakObjectPtr<AEnemyBase> closestTarget = nullptr;
	float minDistanceSquared = FLT_MAX;

	for (const auto& targetPair : targetsInRange)
	{
		TWeakObjectPtr<AEnemyBase> enemy = targetPair.Value;
		if (enemy != nullptr)
		{
			const float squaredDistance = (enemy->GetActorLocation() - position).SizeSquared();
			if (squaredDistance < minDistanceSquared)
			{
				minDistanceSquared = squaredDistance;
				closestTarget = enemy;
			}
		}
	}

	return closestTarget;
}


