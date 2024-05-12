#pragma once
#include <memory>
#include <vector>

#include "Scene.h"
//components, could put in a seperate .h for includes?



//todo: Add removal for components after update method.
namespace dae
{
	class Component;
	class Texture2D;

	class GameObject final
	{
	public:
		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Clear();

		virtual void Update(float deltaTime);
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);



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


		//parent/child functions
		bool HasParent() const
		{
			if (m_pParentGO == nullptr)
			{
				return false;
			}
			return true;
		}

		//child todo: move to private, think abt all of them

		//parent
		void SetParent(GameObject* parent, bool keepWorldPos);
		GameObject* GetParent() const
		{
			return m_pParentGO;
		};
		//dirty flag
		void SetPositionDirty();

		//deletion
		void MarkForDeletion() { m_markedForDeletion = true; };
		bool IsMarkedForDeletion() const { return m_markedForDeletion; };

	private:
		void AddChild(GameObject* childGO);
		void RemoveChild(GameObject* childGO);
		std::vector<std::shared_ptr<dae::Component>> m_pVectorComponents;//todo: REMOVE SHARED PTR!
		std::vector<dae::GameObject*> m_pVectorGOChildren;
		GameObject* m_pParentGO;

		//unused
		bool m_markedForDeletion = false;


	};
}
