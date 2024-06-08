#pragma once
#include "Component.h"
#include "TransformComponent.h"

enum class collisionTag
{
	Player,
	Bag,
	Enemy,
	Gem,
	Tile
};


class CollisionComponent : public dae::Component
{
public:
	CollisionComponent(dae::GameObject* pOwner, collisionTag tag, float radius, bool onlyReceivesCollision = false);
	virtual ~CollisionComponent() override;
	
	void Update(float deltaTime) override;
	void FixedUpdate() override;
	virtual void InitOtherColliderTags() = 0;
	virtual void HandleCollision(collisionTag other, glm::vec3 otherWorldLoc ) = 0;
	void CheckCollision(CollisionComponent* pOtherCollComponent);

	//getters
	bool GetReceivesOnly() const { return m_receiveOnly;};
	float GetCollisionRadius() const { return m_collisionRadius; };
	collisionTag GetCollisionTag() const { return m_collisionTag; };

	glm::vec3 GetOwnerWorldLoc() const { return m_pOwnersTransformComponent->GetWorldPos(); };

private:
	const bool m_receiveOnly{};
	collisionTag m_collisionTag;
	const float m_collisionRadius{};
protected:
	bool m_DoCollision{false};

	dae::TransformComponent* m_pOwnersTransformComponent{};
	std::vector<collisionTag> m_CollidesWithTagsVec{};
};


