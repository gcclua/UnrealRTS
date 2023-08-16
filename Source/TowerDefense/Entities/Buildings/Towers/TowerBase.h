#pragma once

#include "CoreMinimal.h"
#include "TowerState.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "TowerDefense/Entities/Buildings/BuildingBase.h"
#include "VectorTypes.h"
#include "TowerDefense/Entities/Enemies/EnemyBase.h"
#include "TowerBase.generated.h"

UCLASS()
class TOWERDEFENSE_API ATowerBase : public ABuildingBase
{
	GENERATED_BODY()

private:
	ATowerBase();
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditAnywhere)
	double TurnSpeed;

	UPROPERTY(EditAnywhere)
	double FireRate;

	UPROPERTY(EditAnywhere)
	double Range;

	UFUNCTION(BlueprintCallable)
	bool HasTarget();

	UFUNCTION(BlueprintCallable)
	bool FindClosestEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AEnemyBase* CurrentTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* CollisionObject;

private:
	UPROPERTY()
	TMap<FGuid, AEnemyBase*> EnemiesInRange;
	
	TowerState state = TowerState::Idle;
	bool hasTarget = false;
};
