#pragma once
#include "GameFramework/CharacterMovementComponent.h"

#include "IUnit.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UUnit : public UInterface
{
	GENERATED_BODY()
};

class IUnit : public IInterface
{
	GENERATED_BODY()

public:
	virtual UCharacterMovementComponent* GetCharMovement()
	{
		return nullptr;
	}
};
