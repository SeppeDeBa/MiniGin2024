#pragma once
#include <glm/glm.hpp>
class Tile
{
	Tile();
	Tile(int rowPos, int colPos, float tileRadius);
	~Tile();
	

private:
	const glm::vec2 m_gridPos;
	const glm::vec2 m_tileTopLeftPos;
	bool openSides[2][2]{ {false, false }, {false, false } }; //up down left right, all closed by default
	bool fullyOpen{false};
	Tile* connectedTiles[2][2]{};//default all empty up down left right

};

