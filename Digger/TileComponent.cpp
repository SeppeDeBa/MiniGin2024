#include "TileComponent.h"

TileComponent::TileComponent(dae::GameObject* pOwner, int col, int row, float width, float height)
	: Component(pOwner)
	, m_gridPos{col, row}
	, m_width{width}
	, m_height{height}
	, m_tileTopLeftPos{col*width, row*height}
	, m_openSides{{false, false},{false, false}}
	, m_fullyOpen{false}
{

}

TileComponent::~TileComponent()
{
}
