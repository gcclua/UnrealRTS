#pragma once

#include "../Enums/EnemyTypes.h"
#include "EnemyStruct.generated.h"

USTRUCT()
struct FEnemyStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	EnemyType Type;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Blueprint;
};
