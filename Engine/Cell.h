#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "SpriteCodex.h"

class Cell
{
private:
	static constexpr short unsigned int height = 16;
	static constexpr short unsigned int width = 16;

	Vec2 pos; // top left
public:
	Cell(const Vec2& pos);
	void draw(Graphics& gfx) const;
};