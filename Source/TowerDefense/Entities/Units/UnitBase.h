#pragma once

#include "IUnit.h"
#include "UnitState.h"
#include "Components/SphereComponent.h"
#include "TowerDefense/Entities/CharacterEntityBase.h"
#include "TowerDefense/Entities/Bullets/BulletBase.h"
#include "TowerDefense/Entities/Enemies/EnemyBase.h"
#include "TowerDefense/Utils/TargetMonitor.h"
#include "UnitBase.generated.h"

UCLASS()
class TOWERDEFENSE_API AUnitBase : public ACharacterEntityBase, public IUnit
{
	GENERATED_BODY()

protected:

	double nextFireTime = 0;
	
	UnitState state = UnitState::Idle;
	FVector destination;
	TSharedPtr<TargetMonitor> targetMonitor;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	float Range = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	double FireSpeed = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	float RotateSpeed = 20;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Unit")
	USphereComponent* ProximitySphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Unit")
	USceneComponent* FirePositionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit")
	TSubclassOf<ABulletBase> BulletClass;
	
private:
	AUnitBase();

	bool CanFire() const;

	UFUNCTION()
	void OnProximityOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnProximityExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void Fire() const;
public:
	virtual void MoveToLocation(FVector _location) override; 

	virtual bool IsMultiSelectable() override;

	virtual void BeginPlay() override;

	virtual EntityType GetEntityType() override;

	virtual UCharacterMovementComponent* GetCharMovement() override;
	virtual void Tick(float DeltaTime) override;
};
