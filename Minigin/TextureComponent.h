#pragma once
#include "Component.h"
#include <iostream>
#include "Texture2D.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"
namespace dae
{
	class TextureComponent final : public Component
	{
	public:
		TextureComponent(GameObject* pOwner, const std::string& filePath, bool drawAroundCenter);
		TextureComponent(GameObject* pOwner, bool drawAroundCenter);
		~TextureComponent() override;
		void Update(float) override;
		void Render() const override;

		const Texture2D& GetTexture() const;
		void SetTexture(const std::string& filename) { m_pTexture2D = ResourceManager::GetInstance().LoadTexture(filename); SetDirty(); }; //move to cpp
		

		void SetTexture(std::shared_ptr<Texture2D> texture);
		glm::ivec2 GetTextureSize() const;
		bool IsDirty() const { return m_dirtyFlag; };
		void SetDirty() { m_dirtyFlag = true; };
		void DisableDrawing() { if (m_shouldDraw)m_shouldDraw = false; };

	private:
		std::shared_ptr<Texture2D> m_pTexture2D;
		TransformComponent* m_pOwnerTransform{};
		bool m_drawAroundCenter{};
		bool m_newParentTransform{false};

		bool m_shouldDraw{ true };

		//todo: decide if flag is needed here -> could be useful for for example fps component, no time for it yet
		bool m_dirtyFlag;//first put here, but unused so far
	};
}
