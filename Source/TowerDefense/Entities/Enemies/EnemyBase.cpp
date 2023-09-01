#include "EnemyBase.h"

AEnemyBase::AEnemyBase()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
}

bool AEnemyBase::IsSelectable()
{
	return true;
}
