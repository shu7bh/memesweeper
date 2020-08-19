#include "Cell.h"

Cell::Cell(const Vec2& pos, const int tile)
	: pos(pos), tile(static_cast<Tile>(tile)) {}

void Cell::draw(Graphics& gfx) const
{
	switch (tile)
	{
	case Tile::Tile0:
		SpriteCodex::DrawTile0(pos, gfx);
		break;
	case Tile::Tile1:
		SpriteCodex::DrawTile1(pos, gfx);
		break;
	case Tile::Tile2:
		SpriteCodex::DrawTile2(pos, gfx);
		break;
	case Tile::Tile3:
		SpriteCodex::DrawTile3(pos, gfx);
		break;
	case Tile::Tile4:
		SpriteCodex::DrawTile4(pos, gfx);
		break;
	case Tile::Tile5:
		SpriteCodex::DrawTile5(pos, gfx);
		break;
	case Tile::Tile6:
		SpriteCodex::DrawTile6(pos, gfx);
		break;
	case Tile::Tile7:
		SpriteCodex::DrawTile7(pos, gfx);
		break;
	case Tile::Tile8:
		SpriteCodex::DrawTile8(pos, gfx);
		break;
	default:
		break;
	}
}
