#pragma once
#include "Vec2.h"
#include "Cell.h"
#include "Colors.h"
#include "Graphics.h"
#include "SpriteCodex.h"
#include <vector>
#include <memory>

class Board
{
private:
	Vec2 pos; // top left
	const int numCellsWidth, numCellsHeight;
public:
	Board(const Vec2 pos, const int nCW, const int nCH);
	std::vector<std::unique_ptr<Cell>> cells;
	const Color color = Colors::LightGray;
	void draw(Graphics& gfx) const;
};
