#pragma once
#include <Component.h>
#include <glm/glm.hpp>
#include <TextureComponent.h>
class TileComponent : public dae::Component
{
public:
	TileComponent(dae::GameObject* pOwner, int col, int row, float width, float height);
	//Tile(int rowPos, int colPos, float tileRadius);
	~TileComponent();

	void DigTile();
	bool IsOpen() const { return m_DugOut;};

private:
	const glm::vec2 m_gridPos;
	const float m_width;
	const float m_height;
	const glm::vec2 m_tileTopLeftPos;
	bool m_openSides[2][2]; //up down left right, all closed by default
	bool m_fullyOpen;//maybe to be used later?
	bool m_DugOut{ false };




};

