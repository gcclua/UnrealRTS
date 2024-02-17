#include "TowerBase.h"

ATowerBase::ATowerBase()
{
	RootObject = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	this->SetRootComponent(RootObject);

	CollisionObject = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere Object"));
	CollisionObject->SetupAttachment(RootObject);
}

void ATowerBase::BeginPlay()
{
	if (!IsConstruction)
	{
		CollisionObject->SetSphereRadius(range);
		CollisionObject->SetGenerateOverlapEvents(true);
		CollisionObject->SetHiddenInGame(true);
		CollisionObject->OnComponentBeginOverlap.AddDynamic(this, &ATowerBase::OnOverlapBegin);
		CollisionObject->OnComponentEndOverlap.AddDynamic(this, &ATowerBase::OnOverlapEnd);
		CollisionObject->UpdateOverlaps();

		targetMonitor = MakeShared<TargetMonitor>(this);

		// initial overlaps
		TArray<AActor*> OverlappingActors;
		CollisionObject->GetOverlappingActors(OverlappingActors);
		
		for (AActor* Actor : OverlappingActors)
			OnOverlapBegin(CollisionObject, Actor, nullptr, -1, false, FHitResult());
	}

	Super::BeginPlay();
}

void ATowerBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsConstruction || targetMonitor == nullptr)
		return;

	if (!targetMonitor->HasTarget)
		return;
	
	const FVector targetLocation = targetMonitor->GetTarget()->GetActorLocation();
	const FRotator targetRotation = FRotationMatrix::MakeFromX(targetLocation - GetActorLocation()).Rotator();
				
	const FRotator newRotation = FMath::RInterpTo(GetActorRotation(), targetRotation, DeltaSeconds, TurnSpeed);
	SetActorRotation(FRotator(0.0f, newRotation.Yaw, 0.0f));

	const double time = FPlatformTime::Seconds();

	const bool canFire = CanFire();
	const bool canTime = time > nextFireTime;
	if (canTime && canFire)
	{
		Fire();
		nextFireTime = time + fireRate;
	}
}

void ATowerBase::FireFromPoint(USceneComponent* point)
{
	UWorld* world = GetWorld();
	if (world == nullptr || point == nullptr || IsConstruction)
		return;

	FActorSpawnParameters spawnParams;
	const FVector spawnLocation = point->GetComponentLocation();
	const FRotator spawnRotation = point->GetComponentRotation();
    
	ABulletBase* bullet = world->SpawnActor<ABulletBase>(BulletClass, spawnLocation, spawnRotation, spawnParams);
	if (bullet == nullptr)
		return;
	
	bullet->SetActorScale3D(BulletScale);
	bullet->Fire(targetMonitor->GetTarget(), damage);
}

void ATowerBase::UpgradeToLevel(int _level)
{
	if (_level > LevelStats.Num())
		return;

	level = _level;
	
	const FTowerLevelStats stat = LevelStats[level - 1];
	fireRate = stat.FireRate;
	damage = stat.Damage;
	range = stat.Range;

	CollisionObject->SetSphereRadius(range);
	CollisionObject->UpdateOverlaps();
}

bool ATowerBase::CanFire() const
{
	const FVector toTarget = (targetMonitor->GetTarget()->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	const FVector forwardVector = GetActorForwardVector();
	const float dotProduct = FVector::DotProduct(forwardVector, toTarget);

	return dotProduct >= 0.90;
}

void ATowerBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsConstruction && targetMonitor != nullptr)
		targetMonitor->OnOverlapBegin(OtherActor);
}

void ATowerBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!IsConstruction && targetMonitor != nullptr)
		targetMonitor->OnOverlapEnd(OtherActor);
}

EntityType ATowerBase::GetEntityType()
{
	return EntityType::Tower;
}

int ATowerBase::MaxLevel()
{
	return LevelStats.Num();
}

int ATowerBase::NextCostMoney()
{
	if (level >= LevelStats.Num())
		return -1;
	return LevelStats[level].CostMoney;
}

void ATowerBase::Fire_Implementation() { }
