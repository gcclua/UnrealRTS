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

void AUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (state)
	{
		case UnitState::Idle:
			if (targetMonitor->HasTarget)
				state = UnitState::Attacking;
			break;
		case UnitState::WalkingToDestination:
			if (targetMonitor->HasTarget)
				state = UnitState::Attacking;
			break;
		case UnitState::Attacking:
			if (targetMonitor->HasTarget)
			{
				// face the target
				const FVector targetLocation = targetMonitor->GetTarget()->GetActorLocation();
				const FRotator targetRotation = FRotationMatrix::MakeFromX(targetLocation - GetActorLocation()).Rotator();
				
				const FRotator newRotation = FMath::RInterpTo(GetActorRotation(), targetRotation, DeltaTime, RotateSpeed);
				SetActorRotation(FRotator(0.0f, newRotation.Yaw, 0.0f));

				// fire when ready
				const double time = FPlatformTime::Seconds();
				if (time > nextFireTime && CanFire())
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

void AUnitBase::Fire() const
{
	if (!targetMonitor->HasTarget)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;

	FActorSpawnParameters spawnParams;
    
	const FVector spawnLocation = FirePositionComponent->GetComponentLocation();
	const FRotator spawnRotation = FirePositionComponent->GetComponentRotation();
    
	ABulletBase* bullet = world->SpawnActor<ABulletBase>(BulletClass, spawnLocation, spawnRotation, spawnParams);
	bullet->SetActorScale3D(FVector(0.25f, 0.25f, 0.25f));
	bullet->Fire(targetMonitor->GetTarget());
}

bool AUnitBase::CanFire() const
{
	const FVector toTarget = (targetMonitor->GetTarget()->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	const FVector forwardVector = GetActorForwardVector();
	const float dotProduct = FVector::DotProduct(forwardVector, toTarget);
	
	const float aimThresholdDegrees = 11.0f;
	const float aimThreshold = FMath::Cos(FMath::DegreesToRadians(aimThresholdDegrees));

	return dotProduct >= aimThreshold;
}

#pragma region events
void AUnitBase::OnProximityOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (targetMonitor != nullptr)
		targetMonitor->OnOverlapBegin(OtherActor);
}

void AUnitBase::OnProximityExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (targetMonitor != nullptr)
		targetMonitor->OnOverlapEnd(OtherActor);
}
#pragma endregion 

#pragma region crap 
bool AUnitBase::IsSelectable()
{
	return true;
}

void AUnitBase::BeginPlay()
{
	Super::BeginPlay();
	
	targetMonitor = MakeShared<TargetMonitor>(this);
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