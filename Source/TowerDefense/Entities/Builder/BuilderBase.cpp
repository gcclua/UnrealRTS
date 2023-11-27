#include "BuilderBase.h"

bool ABuilderBase::IsBusy() const
{
	return CurrentState == BuilderState::WalkingToJob || CurrentState == BuilderState::DoingJob;
}

EntityType ABuilderBase::GetEntityType()
{
	return EntityType::Builder;
}
