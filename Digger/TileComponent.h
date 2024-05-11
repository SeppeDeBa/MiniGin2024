#pragma once
#include <Component.h>
#include <glm/glm.hpp>
class TileComponent : public dae::Component
{
	TileComponent()
;
	//Tile(int rowPos, int colPos, float tileRadius);
	~TileComponent();


private:
	const glm::vec2 m_gridPos;
	const glm::vec2 m_tileTopLeftPos;
	bool openSides[2][2]{ {false, false }, {false, false } }; //up down left right, all closed by default
	bool fullyOpen{ false };//maybe to be used later?





};

