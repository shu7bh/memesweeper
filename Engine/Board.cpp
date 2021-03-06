#include "Board.h"

#define cell(vec) cells[int(vec.x) * size_t(numCellsWidth) + int(vec.y)]

Board::Board(const int nCW, const int nCH, const int numBombs)
: 
	numCellsWidth(nCW), 
	numCellsHeight(nCH), 
	numBombs(numBombs),
	cells(size_t(numCellsWidth) * numCellsHeight),
	losing(L"Resource\\Losing_sound.wav"),
	Win(L"Resource\\Ta_Da.wav")
{
	static std::random_device rd;
	static std::mt19937_64 generator(rd());
	std::uniform_int_distribution<int> valx(0, numCellsWidth - 1);
	std::uniform_int_distribution<int> valy(0, numCellsHeight - 1);

	pos.x = float(int((Graphics::ScreenWidth - padding - numCellsWidth * (Cell::width + padding)) / 2));
	pos.y = float(int((Graphics::ScreenHeight - padding - numCellsHeight * (Cell::height + padding)) / 2));
	//pos = Vec2(Graphics::ScreenWidth, Graphics::ScreenHeight) / 2 -	Vec2(numCellsWidth, numCellsHeight) / 2;

	for (size_t i = 0; i < cells.size(); ++i)
		cells[i] = std::make_unique<Cell>();

	Vec2 cellPos;
	//  For populating the bombs
	for (auto i = 0; i < numBombs; ++i)
	{
		do
			cellPos = Vec2(valx(generator), valy(generator));
		while (!cell(cellPos)->IsEmpty());

		cell(cellPos) = std::make_unique<Cell>(calCellPos(cellPos), Tile::TileBomb);
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

const int Board::bombInVicinityCounter(const Vec2& cellPos) const
{
	int ct = 0;
	for (auto i = -1; i <= 1; ++i)
		for (auto j = -1; j <=1; ++j)
			if (cellPosIsValid(cellPos + Vec2(i, j)) && cellIsBomb(cellPos + Vec2(i, j)))
				++ct;
	return ct;
}

const Vec2 Board::calCellPos(const Vec2& cellPos) const
{
	return pos + Vec2(padding, padding) * (cellPos + 1) + cellPos * Vec2(Cell::width, Cell::height);
}

const Vec2 Board::calMousePos(const Vec2& mousePos) const
{
	return (mousePos - pos - Vec2(float(padding), float(padding))) / (Vec2(float(padding), float(padding)) + Vec2(Cell::width, Cell::height));
}

void Board::openInVicinity(const Vec2& cellPos)
{
	for (auto i = -1; i <= 1; ++i)
		for (auto j = -1; j <= 1; ++j)
		{
			const Vec2 vicinityCellPos = cellPos + Vec2(i, j);
			if (cellPosIsValid(vicinityCellPos))
			{
				switch (cell(vicinityCellPos)->ts)
				{
				case TileState::Closed:
					cell(vicinityCellPos)->ts = TileState::Opened;
					if (cell(vicinityCellPos)->tile == Tile::Tile0)
						openInVicinity(vicinityCellPos);
					break;

				default:
					break;
				}
			}
		}
}

void Board::RevealAll()
{
	for (auto& cell : cells)
		if (cell->tile == Tile::TileBomb && cell->ts != TileState::Clicked)
			cell->ts = TileState::Opened;
		else if (cell->tile != Tile::TileBomb && cell->ts == TileState::Flagged)
			cell->ts = TileState::Crossed;
}

bool Board::leftIsClicked(MainWindow& wnd)
{
	Vec2 mousePos = calMousePos(Vec2(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()));
	if (mousePos.x >= numCellsWidth || mousePos.x < 0 || mousePos.y >= numCellsHeight || mousePos.y < 0)
		return true;
	const Vec2 temp = mousePos * Vec2(Cell::width + padding, Cell::height + padding);
	if ((int(mousePos.x) * (Cell::width + padding) + Cell::width > temp.x) && 
		(int(mousePos.y) * (Cell::width + padding) + Cell::height > temp.y))
	{
		mousePos = Vec2(int(mousePos.x), int(mousePos.y));
		switch (cell(mousePos)->ts)
		{
		case TileState::Closed:
			cell(mousePos)->ts = TileState::Opened;
			switch (cell(mousePos)->tile)
			{
			case Tile::Tile0:
				openInVicinity(mousePos);
				return true;
			case Tile::TileBomb:
				cell(mousePos)->ts = TileState::Clicked;
				losing.Play();
				RevealAll();
				return false;
			}
			break;
		default:
			break;
		}
	}
	return true;
}

void Board::RightIsClicked(MainWindow& wnd)
{
	const Vec2 mousePos = calMousePos(Vec2(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()));

	if (mousePos.x >= numCellsWidth || mousePos.x < 0 || mousePos.y >= numCellsHeight || mousePos.y < 0)
		return;
	const Vec2 temp = mousePos * Vec2(Cell::width + padding, Cell::height + padding);
	if ((int(mousePos.x) * (Cell::width + padding) + Cell::width > temp.x) &&
		(int(mousePos.y) * (Cell::width + padding) + Cell::height > temp.y))

		switch (cell(mousePos)->ts)
		{
		case TileState::Flagged:
			cell(mousePos)->ts = TileState::Closed;
			break;
		case TileState::Closed:
			cell(mousePos)->ts = TileState::Flagged;
			break;
		default:
			break;
		}
}

bool Board::allNumbersClicked() const
{
	for (const auto& cell : cells)
		switch (cell->tile)
		{
		case Tile::TileBomb:
			break;
		default:
			switch (cell->ts)
			{
			case TileState::Opened:
				break;
			default:
				return false;
			}
			break;
		}
	Win.Play();
	return true;
}

void Board::draw(Graphics& gfx) const
{
	gfx.DrawRect(int(pos.x), int(pos.y), int(pos.x) + numCellsWidth * (Cell::width + padding) + padding,
		int(pos.y) + numCellsHeight * (Cell::height + padding) + padding, color);

	for (int i = int(pos.x); i < int(pos.x) + padding; ++i)
		for (int j = int(pos.y); j < int(calCellPos(Vec2(0, numCellsHeight)).y); ++j)
			gfx.PutPixel(i, j, Colors::Gray);

	for (int i = int(calCellPos(Vec2(numCellsWidth, 0)).x) - 1; i >= int(calCellPos(Vec2(numCellsWidth, 0)).x) - 1 - padding; --i)
		for (int j = int(pos.y); j < int(calCellPos(Vec2(0, numCellsHeight)).y); ++j)
			gfx.PutPixel(i, j, Colors::Gray);

	for (int i = int(pos.x); i < int(calCellPos(Vec2(numCellsWidth, 0)).x); ++i)
		for (int j = int(pos.y); j < int(pos.y) + padding; ++j)
			gfx.PutPixel(i, j, Colors::Gray);

	for (int i = int(pos.x); i < int(calCellPos(Vec2(numCellsWidth, 0)).x); ++i)
		for (int j = int(calCellPos(Vec2(0, numCellsHeight)).y) - 1; j >= int(calCellPos(Vec2(0, numCellsHeight)).y) - 1 - padding; --j)
			gfx.PutPixel(i, j, Colors::Gray);

	for (const auto& cell : cells)
		cell->draw(gfx);
}

#undef cell