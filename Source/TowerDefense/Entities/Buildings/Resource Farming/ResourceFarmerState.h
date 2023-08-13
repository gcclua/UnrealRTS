#pragma once

UENUM(BlueprintType)
enum class ResourceFarmerState : uint8
{
	None = 0,
	Idle,
    Farming,
};