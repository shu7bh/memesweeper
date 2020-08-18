#include "Board.h"

Board::Board(const Vec2 pos, const int nCW, const int nCH)
	: pos(pos), numCellsWidth(nCW), numCellsHeight(nCH) 
{
	cells.push_back(std::make_unique<Cell>(pos));
}

void Board::draw(Graphics& gfx) const
{
	gfx.DrawRect(pos.x, pos.y, pos.x + numCellsWidth * 20, pos.y + numCellsHeight * 20, color);
	SpriteCodex::DrawTile0(pos + Vec2(5, 5), gfx);
	for (const auto& cell : cells)
		cell->draw(gfx);
}
