#pragma once

UENUM(BlueprintType)
enum class UnitCommand : uint8
{
	None = 0,
	Walk,
	Attack,
};