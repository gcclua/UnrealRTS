#pragma once

UENUM(BlueprintType)
enum class BuilderState : uint8
{
	Idle,
	WalkingToJob,
	DoingJob,
};