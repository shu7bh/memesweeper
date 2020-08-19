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
	TileFlag,
	TileBomb
};

class Cell
{
private:
	Vec2 pos; // top left
	bool isEmpty = true;
public:
	Cell() : tile(Tile::Tile0) {}
	Cell(const Vec2& pos, const int tile);
	Cell(const Vec2& pos, const Tile tile);

	void draw(Graphics& gfx) const;

	const bool IsEmpty() const { return isEmpty; }
	const Vec2 Pos() const { return pos; }
	const Tile getTile() const { return tile; }
//#undef createFunc
public:
	static constexpr short unsigned int height = 16;
	static constexpr short unsigned int width = 16;

	const Tile tile;
};