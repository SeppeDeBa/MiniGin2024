#pragma once
#include <memory>
#include "Transform.h"

//components, could put in a seperate .h for includes?


#include "Component.h"
#include <vector>


namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject 
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
		Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_texture{};


		std::vector<std::shared_ptr<dae::Component>> m_pVectorComponents;
	};
}
