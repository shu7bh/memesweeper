#include "Board.h"

Board::Board(const Vec2 pos, const int nCW, const int nCH)
	: pos(pos), numCellsWidth(nCW), numCellsHeight(nCH) 
{
	for (int i = pos.x + padding, ct = 0; i < Graphics::ScreenWidth && ct < numCellsWidth; i += Cell::width + padding, ++ct)
		for (int j = pos.y + padding, ct = 0; j < Graphics::ScreenHeight && ct < numCellsHeight; j += Cell::height + padding, ++ct)
			cells.push_back(std::make_unique<Cell>(Vec2(i, j)));
}

void Board::draw(Graphics& gfx) const
{
	gfx.DrawRect(pos.x, pos.y, pos.x + numCellsWidth * (Cell::width + padding) + padding, 
								pos.y + numCellsHeight * (Cell::height + padding) + padding, color);
	//SpriteCodex::DrawTile0(pos + Vec2(5, 5), gfx);
	for (const auto& cell : cells)
		cell->draw(gfx);
}
