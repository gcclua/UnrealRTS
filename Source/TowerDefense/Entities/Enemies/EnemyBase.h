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
	UPROPERTY(BlueprintReadOnly)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EnemyType enemyType;

	void OnSpawn(AEnemySpawner* enemySpawner, int spawnIndex);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void MoveToTarget(AActor* target);

	virtual bool IsSelectable() override;
	virtual EntityType GetEntityType() override;
};
