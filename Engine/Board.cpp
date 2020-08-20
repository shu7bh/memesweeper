#include "Board.h"

#define cell(vec) cells[int(vec.x) * size_t(numCellsWidth) + int(vec.y)]

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
	//  For populating the bombs
	for (auto i = 0; i < numBombs; ++i)
	{
		do
			cellPos = Vec2(valx(generator), valy(generator));
		while (!cell(cellPos)->IsEmpty());

		cells[cellPos.x * size_t(numCellsWidth) + cellPos.y] = 
			std::make_unique<Cell>(calCellPos(cellPos), Tile::TileBomb);
	}

	// For populating the numbers
	for (auto i = 0; i < numCellsWidth; ++i)
		for (auto j = 0; j < numCellsHeight; ++j)
			if (cell(Vec2(i, j))->IsEmpty())
			{
				Vec2 cellPos(i, j);
				cell(cellPos) = 
					std::make_unique<Cell>(calCellPos(cellPos), bombInVicinityCounter(cellPos));
			}
}

const bool Board::cellPosIsValid(const Vec2& pos) const
{
	return pos.x >= 0 && pos.x < numCellsWidth&& pos.y >= 0 && pos.y < numCellsHeight;
}

const bool Board::cellIsBomb(const Vec2& pos) const
{
	return cell(pos)->getTile() == Tile::TileBomb;
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
	return pos + Vec2(padding, padding) * (cellPos + 1) + cellPos * Vec2(Cell::width, Cell::height);
}

const Vec2 Board::calMousePos(const Vec2& mousePos) const
{
	return (mousePos - pos - Vec2(padding, padding)) / (Vec2(padding, padding) + Vec2(Cell::width, Cell::height));
}

void Board::leftIsClicked (MainWindow& wnd)
{
	const Vec2 mousePos = calMousePos(Vec2(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()));

	if ((int(mousePos.x) + Cell::width > mousePos.x) && (int(mousePos.y) + Cell::height > mousePos.y))
		switch (cell(mousePos)->ts)
		{
		case TileState::NotClicked:
			cell(mousePos)->ts = TileState::Clicked;
			break;
		default:
			break;
		}
}

void Board::RightIsClicked(MainWindow& wnd)
{
	const Vec2 mousePos = calMousePos(Vec2(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()));

	if ((int(mousePos.x) + Cell::width >= mousePos.x) && (int(mousePos.y) + Cell::height >= mousePos.y))
		switch (cell(mousePos)->ts)
		{
		case TileState::Flagged:
			cell(mousePos)->ts = TileState::NotClicked;
			break;
		case TileState::NotClicked:
			cell(mousePos)->ts = TileState::Flagged;
			break;
		default:
			break;
		}
}
#undef cell

void Board::draw(Graphics& gfx) const
{
	gfx.DrawRect(pos.x, pos.y, pos.x + numCellsWidth * (Cell::width + padding) + padding,
		pos.y + numCellsHeight * (Cell::height + padding) + padding, color);

	for (const auto& cell : cells)
		cell->draw(gfx);
}