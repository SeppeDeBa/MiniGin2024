#pragma once
#include <memory>
#include <vector>

#include "Scene.h"
//components, could put in a seperate .h for includes?




namespace dae
{
	class Component;
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:
		virtual void Update(float deltaTime);
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;


		//template functions
		template <typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			m_pVectorComponents.emplace_back(std::make_shared<T>(this, std::forward<Args>(args)...));
			return *static_cast<T*>(m_pVectorComponents.back().get());
		}

		template <typename T>
		void RemoveComponent()
		{
			for (auto i = m_pVectorComponents.begin(); i != m_pVectorComponents.end(); ++i)
			{
				if (dynamic_cast<T*>(i->get()))
				{
					m_pVectorComponents.erase(i);
					break;
				}
			}
		}

		template <typename T>
		T* GetComponent()
		{
			for (auto& component : m_pVectorComponents)
			{
				T* ptr = dynamic_cast<T*>(component.get()); //
				if (ptr)
				{
					return ptr;
				}
			}
			return nullptr;
		}

		template <typename T>
		bool HasComponent() const
		{
			for (auto& component : m_pVectorComponents)
			{
				T* ptr = dynamic_cast<T*>(component.get()); //
				if (ptr)
				{
					return true;
				}
			}
			return false;
		}


	private:
		std::vector<std::shared_ptr<dae::Component>> m_pVectorComponents;
	};
}
