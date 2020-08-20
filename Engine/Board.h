#pragma once
#include "Vec2.h"
#include "Cell.h"
#include "Colors.h"
#include "Graphics.h"
#include "SpriteCodex.h"
#include "MainWindow.h"
#include <vector>
#include <memory>
#include <random>

class Board
{
private:
	Vec2 pos; // top left
	const int numCellsWidth, numCellsHeight;
	const int numBombs;
	static constexpr short int padding = 5;
public:
	Board(const int nCW, const int nCH, const int numBombs);
	std::vector<std::unique_ptr<Cell>> cells;
	const Color color = Colors::LightGray;
	void draw(Graphics& gfx) const;
	void leftIsClicked(MainWindow& wnd);
	void RightIsClicked(MainWindow& wnd);
private:
	const bool cellPosIsValid(const Vec2& pos) const;
	const bool cellIsBomb(const Vec2& pos) const;
	const int bombInVicinityCounter(const Vec2& pos) const;
	const Vec2 calCellPos(const Vec2& cellPos) const;
	const Vec2 calMousePos(const Vec2& mousePos) const;
	void openInVicinity(const Vec2& cellPos);
	void openAllBombs();
};