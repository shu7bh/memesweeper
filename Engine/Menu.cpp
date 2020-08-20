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
	return RectI::FromCenter(mousePos, 0, 0).IsContainedBy(rects[i]);
}

void Menu::hover(const Vec2& mousePos)
{
	const auto temp = highlighted;
	highlighted = Highlighted::None;
	for (auto i = 0; i < rects.size(); ++i)
		if (isContainedBy(mousePos, i)) {
			highlighted = static_cast<Highlighted>(i + 1);
			//Beep.Play();
		}

	if (temp != highlighted && highlighted != Highlighted::None)
		Beep.Play();
}

void Menu::draw(Graphics& gfx) const
{
	SpriteCodex::DrawSmall(rects[0].GetCenter(), gfx);
	SpriteCodex::DrawMedium(rects[1].GetCenter(), gfx);
	SpriteCodex::DrawLarge(rects[2].GetCenter(), gfx);
}

