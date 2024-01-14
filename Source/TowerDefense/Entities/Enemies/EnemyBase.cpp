#include "EnemyBase.h"

#include "TowerDefense/Core/PlayerVitalsBase.h"

AEnemyBase::AEnemyBase()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
}

void AEnemyBase::OnReachTarget(bool success)
{
	rowIndex++;

	AActor* nextTarget = spawner->GetSpawn(rowIndex, innerRowIndex);
	if (nextTarget == nullptr)
	{
		// do damage to player
		const auto playerVitals = Cast<APlayerVitalsBase>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerVitalsBase::StaticClass()));
		playerVitals->OnEnemyReachEnd(this, enemyType, Damage);

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

void AEnemyBase::OnTakeDamage(float _damage)
{
	Health -= _damage;
	if (Health <= 0)
	{
		OnDestroy();
		Destroy();
	}
}

EntityType AEnemyBase::GetEntityType()
{
	return EntityType::Enemy;
}
