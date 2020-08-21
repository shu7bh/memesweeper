#pragma once
#include "Graphics.h"
#include "SpriteCodex.h"
#include "RectI.h"
#include <array>
#include "Sound.h"

class Menu
{
public:
	enum class Highlighted
	{
		None,
		Small,
		Medium,
		Large
	};

public:
	static const std::array<RectI, 3> rects;
	bool isContainedBy( const Vec2& mousePos, const int i) const;
	void hover(const Vec2& mousePos);
	void draw(Graphics& gfx) const;
	Highlighted highlighted = Highlighted::None;
	Sound Beep = Sound(L"Resource\\menu_boop.wav");
};