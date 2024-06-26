#pragma once
#include "SceneManager.h"
namespace dae
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Add(GameObject* object);
		void AddWorldAware(GameObject* object);

		void Remove(std::shared_ptr<GameObject> object);
		void Remove(GameObject* object);

		void RemoveAll();

		void ClearLevel();

		void Update(float deltaTime);
		void FixedUpdate();
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_name;
		std::vector < std::shared_ptr<GameObject>> m_objects{};//TODO MAKE UNIQUE PTRS (although generally unused here)

		
		//using scenes as central owners
		std::vector<GameObject*> m_pGameObjects; //todo: make root scene?
		//players seperate
		std::unique_ptr<GameObject> m_pPlayerOne{};
		std::unique_ptr<GameObject> m_pPlayerTwo{};
		//level seperate
		std::unique_ptr<GameObject> m_pLevelRoot{};
		
		//level


		static unsigned int m_idCounter; 
	};

}
