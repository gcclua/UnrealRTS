#pragma once

#include "TowerDefense/Entities/CharacterEntityBase.h"
#include "TowerDefense/Systems/EnemySpawner.h"
#include "EnemyBase.generated.h"

class AEnemySpawner;

UCLASS()
class TOWERDEFENSE_API AEnemyBase : public ACharacterEntityBase
{
	GENERATED_BODY()

private:
	AEnemyBase();

	UPROPERTY()
	AEnemySpawner* spawner;
	
	int rowIndex;
	int innerRowIndex;

protected:
	UFUNCTION(BlueprintCallable)
	void OnReachTarget(bool success);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyBase")
	int Health;
	
	UPROPERTY(BlueprintReadOnly, Category = "EnemyBase")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyBase")
	EnemyType enemyType;

	void OnSpawn(AEnemySpawner* enemySpawner, int spawnIndex);

	UFUNCTION(BlueprintCallable)
	void OnTakeDamage(float damage);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void MoveToTarget(AActor* target);
	
	virtual EntityType GetEntityType() override;
};
