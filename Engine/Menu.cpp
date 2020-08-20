#include "Menu.h"

void Menu::draw(Graphics& gfx) const
{
	SpriteCodex::DrawSmall(Vec2(gfx.ScreenWidth / 2, gfx.ScreenHeight / 7), gfx);
	SpriteCodex::DrawMedium(Vec2(gfx.ScreenWidth / 2, 3 * gfx.ScreenHeight / 7), gfx);
	SpriteCodex::DrawLarge(Vec2(gfx.ScreenWidth / 2, 5 * gfx.ScreenHeight / 7), gfx);
}
