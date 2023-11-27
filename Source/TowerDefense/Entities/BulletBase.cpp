#include "BulletBase.h"

ABulletBase::ABulletBase()
{
}

EntityType ABulletBase::GetEntityType()
{
	return EntityType::Bullet;
}
