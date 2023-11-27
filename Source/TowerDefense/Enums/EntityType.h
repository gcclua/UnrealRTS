#pragma once

UENUM(BlueprintType)
enum class EntityType : uint8
{
	None = 0,
	Enemy = 1,
	Bullet = 2,
	Unit = 3,
	Builder = 4,
	ResourceFarmer = 5,
	Tower = 6,
};