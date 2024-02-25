#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TextureComponent.h"
#include "TransformComponent.h"


dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float deltaTime)
{
	for (std::shared_ptr<dae::Component> component : m_pVectorComponents)
	{
		component->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (std::shared_ptr<dae::Component> component : m_pVectorComponents)
	{
		component->Render();
	}
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	GetComponent<TextureComponent>()->SetTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	GetComponent<TransformComponent>()->SetPosition(x, y);
}
