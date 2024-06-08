#pragma once
#include "CollisionComponent.h"

class PlayerCollisionComponent : public CollisionComponent
{
public:
	PlayerCollisionComponent(dae::GameObject* pOwner);
	~PlayerCollisionComponent() override = default;
	void InitOtherColliderTags() override;
	void HandleCollision(collisionTag, glm::vec3) override;

};

