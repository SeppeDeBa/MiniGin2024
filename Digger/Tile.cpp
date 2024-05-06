#include "Tile.h"


Tile::Tile(int colPos, int rowPos, float tileRadius)
	: m_gridPos{colPos, rowPos}
	, m_tileTopLeftPos{colPos * tileRadius/* + tileRadius /2.f*/, rowPos * tileRadius/* + tileRadius / 2.f*/ } //properly align to middle
	, openSides{ {true, true}, {true, true } }
{
}

Tile::~Tile()
{
}
