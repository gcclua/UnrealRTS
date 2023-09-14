#include "EnemyBase.h"

AEnemyBase::AEnemyBase()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
}

void AEnemyBase::OnReachTarget(bool success)
{
	AActor* nextTarget = nullptr;
	
	if (!spawner->GetNextSpawn(nextTarget, rowIndex, innerRowIndex))
	{
		// do damage to player
		return;
	}

	MoveToTarget(nextTarget);
}

void AEnemyBase::OnSpawn(AEnemySpawner* enemySpawner, int spawnIndex)
{
	spawner = enemySpawner;

	rowIndex = 0;
	innerRowIndex = spawnIndex;

	OnReachTarget(true);
}

bool AEnemyBase::IsSelectable()
{
	return true;
}
