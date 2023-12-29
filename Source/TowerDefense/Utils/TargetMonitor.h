#pragma once
#include "TowerDefense/Entities/Enemies/EnemyBase.h"

class TargetMonitor
{
private:
	TMap<FGuid, TWeakObjectPtr<AEnemyBase>> targetsInRange;
	TWeakObjectPtr<AEnemyBase> currentTarget;
	TWeakObjectPtr<AActor> attachedActor;
	bool hasTargetInRange = false;

	TWeakObjectPtr<AEnemyBase> FindClosestTarget(const FVector& position);
public:
	bool HasTarget = false;
	
	TargetMonitor(AActor* _attachedActor);
	void OnOverlapBegin(AActor* other);
	void OnOverlapEnd(AActor* other);
	AEnemyBase* GetTarget() const;
	void RecalculateTarget();
};
