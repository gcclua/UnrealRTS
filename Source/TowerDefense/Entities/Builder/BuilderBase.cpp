#include "BuilderBase.h"

bool ABuilderBase::IsBusy() const
{
	return CurrentState == BuilderState::WalkingToJob || CurrentState == BuilderState::DoingJob;
}
