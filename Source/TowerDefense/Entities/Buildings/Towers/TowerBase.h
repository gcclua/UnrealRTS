#pragma once

#include "CoreMinimal.h"
#include "TowerState.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "TowerDefense/Entities/Buildings/BuildingBase.h"
#include "VectorTypes.h"
#include "TowerDefense/Entities/Bullets/BulletBase.h"
#include "TowerDefense/Entities/Enemies/EnemyBase.h"
#include "TowerDefense/Utils/TargetMonitor.h"
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

	bool CanFire() const;
	virtual EntityType GetEntityType() override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
	double TurnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
	double FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
	double Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
	FVector BulletScale;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower")
	TSubclassOf<ABulletBase> BulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
	AEnemyBase* CurrentTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
	USphereComponent* CollisionObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
	USceneComponent* RootObject;

	UFUNCTION(BlueprintNativeEvent)
	void Fire();

	UFUNCTION(BlueprintCallable)
	void FireFromPoint(USceneComponent* point);

private:
	UPROPERTY()
	TMap<FGuid, AEnemyBase*> EnemiesInRange;

	TSharedPtr<TargetMonitor> targetMonitor;
	TowerState state = TowerState::Idle;
	double nextFireTime = -1;
};
