#include "Cell.h"

Cell::Cell(const Vec2& pos)
	: pos(pos) {}

void Cell::draw(Graphics& gfx) const
{
	SpriteCodex::DrawTile0(pos, gfx);
}
