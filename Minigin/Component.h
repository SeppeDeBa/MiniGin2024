#pragma once
#include "GameObject.h"

namespace dae
{
	class Component
	{
	public:
		explicit Component(GameObject* pOwner) : m_pOwnerGO(pOwner) {};
		virtual ~Component() = default;
		virtual void Render() const {};
		virtual void Update(float) {};
		virtual void FixedUpdate() {};
		//ro4
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;



		GameObject* GetGameObject() const
		{
			return m_pOwnerGO;
		}

	private:
		GameObject* m_pOwnerGO{};

	};
}

