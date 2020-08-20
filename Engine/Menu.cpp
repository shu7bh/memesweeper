#include "Menu.h"

const std::array<RectI, 3> Menu::rects =
{
	RectI(RectI::FromCenter(Vec2(Graphics::ScreenWidth / 2, Graphics::ScreenHeight / 7),
						SpriteCodex::sizeselWidth / 2, SpriteCodex::sizeselHeight / 2)),

	RectI(RectI::FromCenter(Vec2(Graphics::ScreenWidth / 2, 3 * Graphics::ScreenHeight / 7),
						SpriteCodex::sizeselWidth / 2, SpriteCodex::sizeselHeight / 2)),

	RectI(RectI::FromCenter(Vec2(Graphics::ScreenWidth / 2, 5 * Graphics::ScreenHeight / 7),
						SpriteCodex::sizeselWidth / 2, SpriteCodex::sizeselHeight / 2)),
};

bool Menu::isContainedBy(const Vec2& mousePos, const int i) const
{
	return rects[i].IsContainedBy( RectI::FromCenter(mousePos,0,0));
}

void Menu::draw(Graphics& gfx) const
{
	SpriteCodex::DrawSmall(rects[0].GetCenter(), gfx);
	SpriteCodex::DrawMedium(rects[1].GetCenter(), gfx);
	SpriteCodex::DrawLarge(rects[2].GetCenter(), gfx);
}
