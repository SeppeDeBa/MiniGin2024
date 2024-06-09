#pragma once
#include "CollisionComponent.h"

#include "Subject.h"

class LivesDisplayComponent;
class PlayerCollisionComponent : public CollisionComponent
{
public:
	PlayerCollisionComponent(dae::GameObject* pOwner, LivesDisplayComponent* mainLivesPtr);
	~PlayerCollisionComponent() override = default;
	void InitOtherColliderTags() override;
	void HandleCollision(collisionTag other, glm::vec3) override;

private:
	Subject<int> m_playerDiesSubject{};
};

