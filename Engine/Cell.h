#pragma once
#include "Vec2.h"
class Cell
{
private:
	static constexpr short unsigned int height = 16;
	static constexpr short unsigned int width = 16;

	Vec2 pos; // top left
public:
	Cell(const Vec2& pos);
};

