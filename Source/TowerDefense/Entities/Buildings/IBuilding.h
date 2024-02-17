#pragma once

#include "IBuilding.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UBuilding : public UInterface
{
	GENERATED_BODY()
};

class IBuilding : public IInterface
{
	GENERATED_BODY()

public:
	virtual int CurrentLevel() = 0;
	virtual int MaxLevel() = 0;
	virtual int NextCostMoney() = 0;
	virtual void UpgradeToLevel(int _level) = 0;
	virtual FString HeaderString() = 0;
};
