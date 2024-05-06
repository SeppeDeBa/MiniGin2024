#pragma once
#include <glm/glm.hpp>
class Tile
{
	Tile(int rowPos, int colPos, float tileRadius);
	~Tile();

private:
	const glm::vec2 m_gridPos;
	const glm::vec2 m_tileTopLeftPos;
	bool openSides[2][2]; //up down left right
	

};

