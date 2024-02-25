#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

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
	const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	GetComponent<TextureComponent>()->SetTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	GetComponent<Transform>()->SetPosition(x, y);
}
