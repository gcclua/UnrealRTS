#pragma once

#include "EnemyContainer.h"
#include "../Enums/EnemyTypes.h"
#include "EnemyStruct.generated.h"

struct FEnemyContainer;

USTRUCT()
struct FEnemyStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	EnemyType Type;

	UPROPERTY(EditAnywhere)
	FEnemyContainer Blueprint;
};
