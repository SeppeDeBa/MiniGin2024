#pragma once
#include "Component.h"
#include "TransformComponent.h"
namespace dae
{
	class CollisionComponent : public Component
	{
		enum class collisionTag
		{
			Player,
			Bag,
			Enemy,
			Gem
		};
	public:
		CollisionComponent(GameObject* pOwner, collisionTag tag, float radius, bool onlyReceivesCollision = false);
		virtual ~CollisionComponent();

		void Update(float deltaTime) override;
		virtual void HandleCollision(collisionTag other) = 0;
		void CheckCollision(CollisionComponent* pOtherCollComponent);
		virtual void Collide();
		bool GetReceivesOnly()const { return m_receiveOnly; };

	private:
		const bool m_receiveOnly{};
		collisionTag m_collisionTag;
		TransformComponent* m_pOwnersTransformComponent{};
		const float m_collisionRadius{};
	};
}

