// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSAIController.h"

ARTSAIController::ARTSAIController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{

}
