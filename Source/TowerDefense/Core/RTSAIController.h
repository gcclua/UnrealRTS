#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIModule/Classes/Navigation/CrowdFollowingComponent.h"
#include "RTSAIController.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ARTSAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ARTSAIController(const FObjectInitializer& ObjectInitializer);
};
