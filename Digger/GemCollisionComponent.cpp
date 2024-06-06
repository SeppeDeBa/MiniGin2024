#include "GemCollisionComponent.h"

GemCollisionComponent::GemCollisionComponent(dae::GameObject* pOwner)
	:CollisionComponent(pOwner, collisionTag::Gem, 22.f, true)
{
}
