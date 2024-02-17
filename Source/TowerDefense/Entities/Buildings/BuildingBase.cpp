#include "BuildingBase.h"

#include "TowerDefense/Systems/BuilderManager.h"

void ABuildingBase::OnSpawn()
{
	if (IsConstruction)
	{
		ABuilderManager* builderManager = Cast<ABuilderManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ABuilderManager::StaticClass()));
		builderManager->RequestBuilder(this);
	}
	else
	{
		OnPlace();
	}
}

void ABuildingBase::OnPlace_Implementation()
{
	level = 1;
	UpgradeToLevel(level);
}

void ABuildingBase::OnDoneConstructing()
{
	if (!IsConstruction || RealBuildingClass == nullptr)
		return;

	const FActorSpawnParameters spawnParams;

	ABuildingBase* building = GetWorld()->SpawnActor<ABuildingBase>(RealBuildingClass, GetActorTransform().GetLocation(), GetActorTransform().GetRotation().Rotator(), spawnParams);
	building->OnPlace();

	UnregisterAndDestroy();
}

bool ABuildingBase::IsMultiSelectable()
{
	return false;
}

void ABuildingBase::UpgradeToLevel(int _level)
{
	// base implementation
}

int ABuildingBase::CurrentLevel()
{
	return level;
}

int ABuildingBase::MaxLevel()
{
	return 1;
}

int ABuildingBase::NextCostMoney()
{
	return -1;
}

FString ABuildingBase::HeaderString()
{
	return NameString;
}
