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

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd) {}

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
		menu.hover(Vec2(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()));
		if (wnd.mouse.LeftIsPressed())
			if (!inhibitLeftMouseClick)
			{
				inhibitLeftMouseClick = true;
				switch (menu.highlighted)
				{
				case Menu::Highlighted::Small:
					board = std::make_unique<Board>(9, 9, 10);
					state = State::Running;
					break;
				case Menu::Highlighted::Medium:
					board = std::make_unique<Board>(16, 16, 40);
					state = State::Running;
					break;
				case Menu::Highlighted::Large:
					board = std::make_unique<Board>(25, 25, 99);
					state = State::Running;
					break;
				default:
					break;
				}
			}
			else;
		else
			inhibitLeftMouseClick = false;
		break;
	case State::Running:
		if (wnd.mouse.LeftIsPressed())
			if (!inhibitLeftMouseClick)
			{
				inhibitLeftMouseClick = true;
				if (!board->leftIsClicked(wnd))
					state = State::End;
			}
			else;
		else
			inhibitLeftMouseClick = false;

		if (wnd.mouse.RightIsPressed())
			if (!inhibitRightMouseClick)
				board->RightIsClicked(wnd), inhibitRightMouseClick = true;
			else;
		else
			inhibitRightMouseClick = false;
		break;

	case State::End:
		if (wnd.mouse.LeftIsPressed())
			if (!inhibitLeftMouseClick)
				state = State::Menu, inhibitLeftMouseClick = true;
			else;
		else
			inhibitLeftMouseClick = false;

		if (wnd.mouse.RightIsPressed())
			if (!inhibitRightMouseClick)
				state = State::Menu, inhibitRightMouseClick = true;
			else;
		else
			inhibitRightMouseClick = false;
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
		menu.draw(gfx);
		break;
	case State::Running:
	case State::End:
		board->draw(gfx);
		break;
	default:
		break;
	}
}
