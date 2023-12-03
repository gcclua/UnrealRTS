#pragma once

UENUM(BlueprintType)
enum class UnitState : uint8
{
	Idle = 0,
	WalkingToDestination,
	Attacking,
};