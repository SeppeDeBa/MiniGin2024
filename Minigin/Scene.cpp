#include "Scene.h"
#include "GameObject.h"

#include <algorithm>


using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene()
{
	RemoveAll(); //should clean up
}

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Add(GameObject* object)
{

	m_pGameObjects.push_back(object);
}

void dae::Scene::AddWorldAware(GameObject*)
{
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::Remove(GameObject* object)
{
	m_pGameObjects.erase(std::remove(m_pGameObjects.begin(), m_pGameObjects.end(), object), m_pGameObjects.end());
}

void Scene::RemoveAll()
{
	for (GameObject* go : m_pGameObjects)
	{
		delete go;
		go = nullptr;
	}
}

void dae::Scene::ClearLevel()
{
	m_pLevelRoot.reset();
	m_pLevelRoot = std::make_unique<GameObject>();
}

void Scene::Update(float deltaTime)
{
	for (GameObject* go : m_pGameObjects)
	{
		go->Update(deltaTime);
	}

	auto it = m_pGameObjects.begin();
	while (it != m_pGameObjects.end())
	{
		GameObject* go = *it;
		if (go->IsMarkedForDeletion())
		{
			delete go;
			it = m_pGameObjects.erase(it); //remove from vector and advance iterator
		}
		++it;
	}
}

void Scene::FixedUpdate()
{
	for (GameObject* go : m_pGameObjects)
	{
		go->FixedUpdate();
	}
}

//todo: Should deletion be here?
void Scene::Render() const
{
	for (GameObject* go : m_pGameObjects)
	{
		go->Render();
	}
}

