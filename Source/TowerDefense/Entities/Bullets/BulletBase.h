#pragma once

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TowerDefense/Entities/BaseEntity.h"
#include "TowerDefense/Enums/BulletType.h"
#include "BulletBase.generated.h"

UCLASS(ABSTRACT)
class TOWERDEFENSE_API ABulletBase : public ABaseEntity
{
	GENERATED_BODY()

protected:
	float GetDamage() const;
	void DestroyBullet();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	ABulletBase();

	UPROPERTY(BlueprintReadWrite, Category = "Bullet")
	BulletType BulletType;

	UPROPERTY(VisibleDefaultsOnly, Category = "Bullet")
	USceneComponent* RootObject;
	
	UPROPERTY(BlueprintReadWrite, Category = "Bullet")
	USphereComponent* Collider;

	UPROPERTY(BlueprintReadWrite, Category = "Bullet")
	UProjectileMovementComponent* ProjectileMovement;

	UFUNCTION(BlueprintCallable)
	virtual void Fire(AActor* target);

	virtual EntityType GetEntityType() override;
};
