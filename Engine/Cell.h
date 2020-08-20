#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "SpriteCodex.h"

enum class Tile : char
{
	Tile0,
	Tile1,
	Tile2,
	Tile3,
	Tile4,
	Tile5,
	Tile6,
	Tile7,
	Tile8,
	TileBomb,
};

enum class TileState : char
{
	Closed,
	Opened,
	Flagged
};

class Cell
{
private:
	bool isEmpty = true;
public:
	// Constructor
	Cell() : pos(Vec2()), tile(Tile::Tile0) {}
	Cell(const Vec2& pos, const int tile);
	Cell(const Vec2& pos, const Tile tile);

	void draw(Graphics& gfx) const;

	// Getters
	const bool IsEmpty() const { return isEmpty; }
	const Vec2 Pos() const { return pos; }
	const Tile getTile() const { return tile; }
public:
	Vec2 pos; // top left
	static constexpr short unsigned int height = 16;
	static constexpr short unsigned int width = 16;

	const Tile tile;
	TileState ts = TileState::Closed;
};