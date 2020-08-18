/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
}

#include "SpriteCodex.h"
void Game::ComposeFrame()
{

	SpriteCodex::DrawTile0(Vec2(150, 250), gfx);
	SpriteCodex::DrawTile1(Vec2(200, 250), gfx);
	SpriteCodex::DrawTile2(Vec2(250, 250), gfx);
	SpriteCodex::DrawTile3(Vec2(300, 250), gfx);
	SpriteCodex::DrawTile4(Vec2(350, 250), gfx);
	SpriteCodex::DrawTile5(Vec2(400, 250), gfx);
	SpriteCodex::DrawTile6(Vec2(450, 250), gfx);
	SpriteCodex::DrawTile7(Vec2(500, 250), gfx);
	SpriteCodex::DrawTile8(Vec2(550, 250), gfx);
	SpriteCodex::DrawTileButton(Vec2(600, 250), gfx);
	SpriteCodex::DrawTileCross(Vec2(650, 250), gfx);
	SpriteCodex::DrawTileFlag(Vec2(750, 250), gfx);
	SpriteCodex::DrawTileBomb(Vec2(700, 150), gfx);
	SpriteCodex::DrawTileBombRed(Vec2(650, 150), gfx);
}
