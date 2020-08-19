#include "Board.h"

Board::Board(const Vec2 pos, const int nCW, const int nCH, const int numBombs)
: 
	pos(pos), 
	numCellsWidth(nCW), 
	numCellsHeight(nCH), 
	numBombs(numBombs),
	cells(size_t(numCellsWidth) * numCellsHeight)
{
	static std::random_device rd;
	static std::mt19937_64 generator(rd());
	static std::uniform_int_distribution<int> valx(0, numCellsWidth - 1);
	static std::uniform_int_distribution<int> valy(0, numCellsHeight - 1);

	for (size_t i = 0; i < cells.size(); ++i)
		cells[i] = std::make_unique<Cell>();

	Vec2 cellPos;
	for (auto i = 0; i < numBombs; ++i)
	{
		do
			cellPos = Vec2(valx(generator), valy(generator));
		while (!cells[cellPos.x * size_t(numCellsWidth) + cellPos.y]->IsEmpty());

		cells[cellPos.x * size_t(numCellsWidth) + cellPos.y] = 
			std::make_unique<Cell>(calCellPos(cellPos), Tile::TileBomb);
	}

	for (auto i = 0; i < numCellsWidth; ++i)
		for (auto j = 0; j < numCellsHeight; ++j)
			if (cells[i * size_t(numCellsWidth) + j]->IsEmpty())
			{
				Vec2 cellPos(i, j);
				cells[i * size_t(numCellsWidth) + j] = 
					std::make_unique<Cell>(calCellPos(cellPos), bombInVicinityCounter(cellPos));
			}
}

void Board::draw(Graphics& gfx) const
{
	gfx.DrawRect(pos.x, pos.y, pos.x + numCellsWidth * (Cell::width + padding) + padding, 
								pos.y + numCellsHeight * (Cell::height + padding) + padding, color);
	//SpriteCodex::DrawTile0(pos + Vec2(5, 5), gfx);
	for (const auto& cell : cells)
		cell->draw(gfx);
}

const bool Board::cellPosIsValid(const Vec2& pos) const
{
	return pos.x >= 0 && pos.x < numCellsWidth&& pos.y >= 0 && pos.y < numCellsHeight;
}

const bool Board::cellIsBomb(const Vec2& pos) const
{
	return cells[pos.x * size_t(numCellsWidth) + pos.y]->getTile() == Tile::TileBomb;
}

const int Board::bombInVicinityCounter(const Vec2& pos) const
{
	int ct = 0;
	for (auto i = -1; i <= 1; ++i)
		for (auto j = -1; j <=1; ++j)
			if (cellPosIsValid(pos + Vec2(i, j)) && cellIsBomb(pos + Vec2(i, j)))
				++ct;
	return ct;
}

const Vec2 Board::calCellPos(const Vec2& cellPos) const
{
	return Vec2(pos + Vec2(padding, padding) * (cellPos + 1) + cellPos * Vec2(Cell::width, Cell::height));
}
