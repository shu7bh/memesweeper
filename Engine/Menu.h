#pragma once
#include "Graphics.h"
#include "SpriteCodex.h"
#include "RectI.h"
#include <array>

class Menu
{
private:
public:
	static const std::array<RectI, 3> rects;
	bool isContainedBy( const Vec2& mousePos, const int i) const;
	void draw(Graphics& gfx) const;
};