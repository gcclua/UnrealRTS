#include "UnitBase.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "TowerDefense/Entities/Enemies/EnemyBase.h"

AUnitBase::AUnitBase()
{
	ProximitySphere = CreateDefaultSubobject<USphereComponent>(TEXT("ProximitySphere"));
	ProximitySphere->SetupAttachment(RootComponent);
	ProximitySphere->SetSphereRadius(100.0f);
	ProximitySphere->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	ProximitySphere->OnComponentBeginOverlap.AddDynamic(this, &AUnitBase::OnProximityOverlap);
	ProximitySphere->OnComponentEndOverlap.AddDynamic(this, &AUnitBase::OnProximityExit);

	FirePositionComponent = CreateDefaultSubobject<USceneComponent>(TEXT("FirePositionComponent"));
	FirePositionComponent->SetupAttachment(RootComponent); 
}

void AUnitBase::MoveToLocation(FVector _location)
{
	destination = _location;

	AAIController* AIController = Cast<AAIController>(GetController());
	
	if (AIController != nullptr)
	{
		float acceptanceRadius = 0;
		bool stopOnOverlap = true;
		bool usePathfinding = true;
		bool canStrafe = false;
		bool projectDestinationToNavigation = true;
		TSubclassOf<UNavigationQueryFilter> filterClass = nullptr;
		bool allowPartialPath = true;
		
		AIController->MoveToLocation(destination, acceptanceRadius, stopOnOverlap,
									 usePathfinding, canStrafe,
							 projectDestinationToNavigation, filterClass, allowPartialPath);
	}
}

bool AUnitBase::GetTarget()
{
	if (enemiesInRange.Num() == 0)
		return false;

	FGuid minGuid;
	double minDist = 999999;
	const FVector thisPos = this->GetActorLocation();

	for (const TTuple<FGuid, AEnemyBase*> keyVal : enemiesInRange)
	{
		FVector location = keyVal.Value->GetActorLocation();
		const double dist = UE::Geometry::Distance(thisPos, location);

		if (dist < minDist)
		{
			minDist = dist;
			minGuid = keyVal.Key;
		}
	}

	currentTarget = enemiesInRange[minGuid];
	hasTarget = true;

	return true;
}

void AUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (state)
	{
		case UnitState::Idle:
			if (targetsInRange && GetTarget())
				state = UnitState::Attacking;
			break;
		case UnitState::WalkingToDestination:
			if (targetsInRange && GetTarget())
				state = UnitState::Attacking;
			break;
		case UnitState::Attacking:
			if (hasTarget)
			{
				// face the target
				const FVector targetLocation = currentTarget->GetActorLocation();
				const FRotator targetRotation = FRotationMatrix::MakeFromX(targetLocation - GetActorLocation()).Rotator();
				
				const FRotator newRotation = FMath::RInterpTo(GetActorRotation(), targetRotation, DeltaTime, RotateSpeed);
				SetActorRotation(FRotator(0.0f, newRotation.Yaw, 0.0f));

				// fire when ready
				const double time = FPlatformTime::Seconds();
				if (time > nextFireTime)
				{
					Fire();
					nextFireTime = time + FireSpeed;
				}
			}
			else
			{
				state = UnitState::Idle;
			}
			break;
	}
}

void AUnitBase::Fire()
{
	if (!currentTarget)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;

	// Check if we're facing the target closely enough to fire
	FVector toTarget = (currentTarget->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	FVector forwardVector = GetActorForwardVector();
	float dotProduct = FVector::DotProduct(forwardVector, toTarget);
    
	// Adjust this threshold value to control how directly the unit must be facing the target to fire
	const float aimThreshold = 0.98f; // Cosine of about 11 degrees

	if (dotProduct >= aimThreshold)
	{
		FActorSpawnParameters spawnParams;
        
		const FVector spawnLocation = FirePositionComponent->GetComponentLocation();
		const FRotator spawnRotation = FirePositionComponent->GetComponentRotation();
        
		ABulletBase* bullet = world->SpawnActor<ABulletBase>(BulletClass, spawnLocation, spawnRotation, spawnParams);
		bullet->SetActorScale3D(FVector(0.25f, 0.25f, 0.25f));
		bullet->Fire(currentTarget);
	}
}

#pragma region events
void AUnitBase::OnProximityOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr)
		return;

	AEnemyBase* enemy = Cast<AEnemyBase>(OtherActor);
	if (enemy == nullptr)
		return;

	const FGuid guid = OtherActor->GetActorGuid();
	if (enemiesInRange.Contains(guid))
		return;

	enemiesInRange.Add(guid, enemy);
	if (!targetsInRange)
		targetsInRange = true;
}

void AUnitBase::OnProximityExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == nullptr)
		return;
	
	const AEnemyBase* enemy = Cast<AEnemyBase>(OtherActor);
	if (enemy == nullptr)
		return;

	const FGuid guid = enemy->GetActorGuid();
	if (!enemiesInRange.Contains(guid))
		return;

	enemiesInRange.Remove(guid);

	if (enemiesInRange.Num() == 0)
	{
		hasTarget = false;
		targetsInRange = false;
	}
	else if (currentTarget != nullptr && currentTarget->GetActorGuid() == guid)
		hasTarget = false;
}
#pragma endregion 

#pragma region crap 
bool AUnitBase::IsSelectable()
{
	return true;
}

EntityType AUnitBase::GetEntityType()
{
	return EntityType::Unit;
}

UCharacterMovementComponent* AUnitBase::GetCharMovement()
{
	return GetCharacterMovement();
}
#pragma endregion 