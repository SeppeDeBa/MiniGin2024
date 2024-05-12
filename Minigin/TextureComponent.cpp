#include "TextureComponent.h"
dae::TextureComponent::TextureComponent(GameObject* pOwner, const std::string& filePath, bool drawAroundCenter)
	: Component(pOwner)
	, m_pTexture2D{ ResourceManager::GetInstance().LoadTexture(filePath) }
	, m_drawAroundCenter{ drawAroundCenter }
	, m_dirtyFlag{ true }
{

}

dae::TextureComponent::TextureComponent(GameObject* pOwner, bool drawAroundCenter)
	: Component(pOwner)
	, m_pTexture2D{}
	, m_drawAroundCenter{ drawAroundCenter }
	, m_dirtyFlag{true}
{

}



dae::TextureComponent::~TextureComponent()
{
	if (m_pTexture2D != nullptr)
	{
		m_pTexture2D = nullptr;
	}
	if (m_pOwnerTransform != nullptr)
	{
		m_pOwnerTransform = nullptr;
	}
}


void dae::TextureComponent::Update(float)
{
	if (m_pOwnerTransform == nullptr || m_newParentTransform)
	{
		m_pOwnerTransform = GetGameObject()->GetComponent<TransformComponent>();
	}
}

void dae::TextureComponent::Render() const
{
	if (m_pTexture2D != nullptr && m_pOwnerTransform != nullptr)
	{
		if (m_drawAroundCenter)
		{
			Renderer::GetInstance().RenderTexture(*m_pTexture2D
				, m_pOwnerTransform->GetWorldPos().x - static_cast<float>(GetTextureSize().x) / 2.f
				, m_pOwnerTransform->GetWorldPos().y - static_cast<float>(GetTextureSize().y) / 2.f);
		}
		else
		{
			Renderer::GetInstance().RenderTexture(*m_pTexture2D
				, m_pOwnerTransform->GetWorldPos().x
				, m_pOwnerTransform->GetWorldPos().y);
		}
	}
}

const dae::Texture2D& dae::TextureComponent::GetTexture() const
{
	return *m_pTexture2D;
}

void dae::TextureComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_pTexture2D = texture;
	SetDirty();
}

glm::ivec2 dae::TextureComponent::GetTextureSize() const
{
	return m_pTexture2D->GetSize();
}

