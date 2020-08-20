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
	gfx( wnd ),
	board(20, 20, 60) {}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	switch (state)
	{
	case State::Menu:
		break;
	case State::Running:
		if (wnd.mouse.LeftIsPressed())
			if (!board.leftIsClicked(wnd))
				state = State::End;

		if (wnd.mouse.RightIsPressed())
			if (!inhibitRightMouseClick)
				board.RightIsClicked(wnd), inhibitRightMouseClick = true;
			else;
		else
			inhibitRightMouseClick = false;
		break;
	case State::End:
		if (wnd.mouse.LeftIsPressed() || wnd.mouse.RightIsPressed())
			State::Menu;
		break;
	default:
		break;
	}

}

void Game::ComposeFrame()
{	
	switch (state)
	{
	case State::Menu:
		break;
	case State::Running:
		board.draw(gfx);
		break;
	case State::End:
		break;
	default:
		break;
	}
}
