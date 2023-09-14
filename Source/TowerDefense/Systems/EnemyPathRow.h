#pragma once

#include "EnemyPathRow.generated.h"

USTRUCT(BlueprintType)
struct FEnemyPathRow
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> Points;
};
