#include "TileComponent.h"
#include <iostream>
TileComponent::TileComponent(dae::GameObject* pOwner, int col, int row, float width, float height)
	: Component(pOwner)
	, m_gridPos{col, row}
	, m_width{width}
	, m_height{height}
	, m_tileTopLeftPos{col*width, row*height + height + height}
{

}

TileComponent::~TileComponent()
{
}

void TileComponent::DigTile()
{
	if (!m_DugOut)
	{
		dae::TextureComponent* pOwnerTextureComponent{ GetGameObject()->GetComponent<dae::TextureComponent>() };
		if (pOwnerTextureComponent)
		{
			pOwnerTextureComponent->DisableDrawing();
			m_DugOut = true;

		}
		else
		{
			std::cout << "invalid texture not linked to a tile" << std::endl;
		}
	}
}

void TileComponent::FillTile()
{
	if (m_DugOut)
	{
		dae::TextureComponent* pOwnerTextureComponent{ GetGameObject()->GetComponent<dae::TextureComponent>() };
		if (pOwnerTextureComponent)
		{
			pOwnerTextureComponent->EnableDrawing();
			m_DugOut = false;

		}
		else
		{
			std::cout << "invalid texture not linked to a tile" << std::endl;
		}
	}
}


