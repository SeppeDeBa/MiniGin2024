#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "Component.h"
#include <algorithm>

#include "Transform.h"



dae::GameObject::GameObject()
	:m_pParentGO(nullptr)
{
	
}
dae::GameObject::~GameObject()
{
	for (GameObject* go : m_pVectorGOChildren)
	{
		go = nullptr;
	}
	m_pParentGO = nullptr;
}

void dae::GameObject::Clear()
{
	for (GameObject* go : m_pVectorGOChildren)
	{
		go = nullptr;
	}
}

void dae::GameObject::Update(float deltaTime)
{
	//update self
	if (m_enabled)
	{
		for (std::shared_ptr<dae::Component> component : m_pVectorComponents)
		{
			component->Update(deltaTime);
		}
		//update children
		for (dae::GameObject* go : m_pVectorGOChildren)
		{
			go->Update(deltaTime);
		}
	}
}

void dae::GameObject::Render() const
{
	if (m_enabled)
	{
		for (std::shared_ptr<dae::Component> component : m_pVectorComponents)
		{
			component->Render();
		}
	}
}


void dae::GameObject::AddChild(GameObject* childGO)
{
	m_pVectorGOChildren.push_back(childGO);
}

void dae::GameObject::RemoveChild(GameObject* childGO)//todo: check ppt to update this function. focus after this week bc sick
{
	const auto childGODeleteIt = std::find(m_pVectorGOChildren.begin(), m_pVectorGOChildren.end(), childGO);
	if (childGODeleteIt != m_pVectorGOChildren.end())
	{
		m_pVectorGOChildren.erase(childGODeleteIt); //needs to be removed from the scene!
	}
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPos)
{
	if (m_pParentGO == nullptr)
	{
		GetComponent<TransformComponent>()->SetLocalPosition(GetComponent<TransformComponent>()->GetWorldPos());
	}
	else
	{
		if (keepWorldPos)//TODO: ASK ALEX WHAT HE MEANS LOGIC MISTAKE
		{
			GetComponent<TransformComponent>()->SetLocalPosition(
													GetComponent<TransformComponent>()->GetLocalPos() - 
													m_pParentGO->GetComponent<TransformComponent>()->GetWorldPos()); //slide 21 does this needs to substract local pos aswell?
		}
		SetPositionDirty();
	}

	//2. Remove this child from parent
	if (m_pParentGO)//todo: could be in previous else?
	{
		m_pParentGO->RemoveChild(this);
	}

	//3. Set new parent as this childs parent
	m_pParentGO = parent;

	//4. Add this child to parents list of children
	if (m_pParentGO)
	{
		m_pParentGO->AddChild(this);
	}
}

void dae::GameObject::SetPositionDirty()
{
	GetComponent<TransformComponent>()->SetTransformDirty();
	for (GameObject* go : m_pVectorGOChildren)
	{
		go->SetPositionDirty();
	}
}



void dae::GameObject::SetTexture(const std::string& filename)
{
	GetComponent<TextureComponent>()->SetTexture(filename);
	
}

void dae::GameObject::SetPosition(float x, float y)
{
	GetComponent<TransformComponent>()->SetLocalPosition(x, y);
	SetPositionDirty();
}
