#include "BuilderManager.h"

bool ABuilderManager::TrySendOutBuilder()
{
	if (buildingQueue.IsEmpty())
		return false;
	
	ABuilderBase* builder = nullptr;
	for (ABuilderBase* _builder : Builders)
	{
		if (!_builder->IsBusy())
		{
			builder = _builder;
			break;
		}
	}

	if (builder == nullptr)
		return false;

	ABuildingBase* building = nullptr;
	buildingQueue.Dequeue(building);
	
	builder->OnStartJob(building);
	
	return true;
}

bool ABuilderManager::RequestBuilder(ABuildingBase* building)
{
	buildingQueue.Enqueue(building);
	return TrySendOutBuilder();
}

void ABuilderManager::OnCompleteBuild(ABuilderBase* builder)
{
	TrySendOutBuilder();
}

void ABuilderManager::BeginPlay()
{
	for (int i = 0; i < NumBuilders; i++)
	{
		const FActorSpawnParameters spawnParams;
		const auto actor = GetWorld()->SpawnActor<AActor>(BuilderClass, SpawnTransform->GetActorLocation(), SpawnTransform->GetActorRotation(), spawnParams);
		ABuilderBase* builder = Cast<ABuilderBase>(actor);
		
		Builders.Add(builder);
	}
	
	Super::BeginPlay();
}
