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
			Enemy
		};
	public:
		CollisionComponent(GameObject* pOwner, collisionTag tag, bool onlyReceivesCollision = false);
		~CollisionComponent();

		void Update(float deltaTime) override;
		virtual void HandleCollision(collisionTag other) = 0;
		virtual void Collide();
		bool GetReceivesOnly()const { return m_receiveOnly; };

	private:
		const bool m_receiveOnly{};
		collisionTag m_collisionTag;
		TransformComponent* m_pOwnersTransformComponent{};
	};
}

