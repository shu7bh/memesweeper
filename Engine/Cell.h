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
public:
	Cell(const Vec2& pos, const int tile);
	void draw(Graphics& gfx) const;
public:
	static constexpr short unsigned int height = 16;
	static constexpr short unsigned int width = 16;

	const Tile tile;
};