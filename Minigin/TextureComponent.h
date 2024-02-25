#pragma once
#include "Component.h"
#include <iostream>
#include "Texture2D.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"
namespace dae
{
	class TextureComponent : public Component
	{
	public:
		TextureComponent(GameObject* pOwner, const std::string& filePath, bool drawAroundCenter);
		TextureComponent(GameObject* pOwner, bool drawAroundCenter);
		~TextureComponent() override;
		void Update(float deltaTime) override;
		void Render() const override;


		const Texture2D& GetTexture() const;
		void SetTexture(const std::string& filename) { m_pTexture2D = ResourceManager::GetInstance().LoadTexture(filename); };


		void SetTexture(std::shared_ptr<Texture2D> texture);
		glm::ivec2 GetTextureSize() const;


	private:
		std::shared_ptr<Texture2D> m_pTexture2D;
		Transform* m_pOwnerTransform{};
		bool m_drawAroundCenter{};
		bool m_newParentTransform{false};
	};
}
