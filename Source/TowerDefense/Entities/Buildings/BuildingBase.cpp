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
