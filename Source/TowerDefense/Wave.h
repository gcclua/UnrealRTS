#pragma once

#include "SubWave.h"
#include "Wave.generated.h"

USTRUCT()
struct FWave
{
	GENERATED_USTRUCT_BODY()
	
public:
	FWave();
	
	UPROPERTY(EditAnywhere)
	TArray<FSubWave> SubWaves;
};
