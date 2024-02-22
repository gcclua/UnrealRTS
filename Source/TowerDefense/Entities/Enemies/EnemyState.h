#pragma once

UENUM(BlueprintType)
enum class EnemyState : uint8
{
	Idle = 0,
	Running = 1,
	Attacking = 2,
	Dead = 3,
};