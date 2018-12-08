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
#include "RabbitPen.h"
#include "Rabbit.h"

#include <chrono>
#include <random>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rabbitpen(gfx),
	rng (std::random_device()())
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
	Sleep(2000);
}

void Game::UpdateModel()
{
	for (int i = 0; i < number_of_rabbits; i++)
	{
	rabbit[i].Move(NewLocation(i));

	}
}

void Game::ComposeFrame()
{
	std::uniform_int_distribution<int> cdist(0, 255);
	Location loc = { 20,20 };
	for (int i = 0; i < number_of_rabbits; i++)
	rabbit[i].DrawBunny(rabbitpen);
}

Location Game::NewLocation(int i )
{
	Location nextloc, locholder;
	locholder = rabbit[i].GetLoc();
	std::uniform_int_distribution<int> newloc(1, 4);
	switch (newloc(rng))
	{
	case (1):
		nextloc = { -1,0 };
		if (!IsInPen(locholder, nextloc, rabbitpen))
		{
			nextloc = { 0,0 };
		}
		return nextloc;
		break;
	case (2):
		nextloc = { 1,0 };
		if (!IsInPen(locholder, nextloc, rabbitpen))
		{
			nextloc = { 0,0 };
		}
		return nextloc;
		break;
	case (3):
		nextloc = { 0, -1 };
		if (!IsInPen(locholder, nextloc, rabbitpen))
		{
			nextloc = { 0,0 };
		}
		return nextloc;
		break;
	case (4):
		nextloc = { 0,1 };
		if (!IsInPen(locholder, nextloc, rabbitpen))
		{
			nextloc = { 0,0 };
		}
		return nextloc;
		break;
	}

	
}
bool Game::IsInPen(Location& loc, Location& next_loc, RabbitPen& pen)
{
	{
		Location testloc = { loc.x + next_loc.x, loc.y + next_loc.y };
		if (testloc.x < 0 ||
			testloc.y < 0 ||
			testloc.x >= pen.GetPenWidth() ||
			testloc.y >= pen.GetPenHeight() )
		{
			return false;
		}
		else
		{
			return true;
		}

	}
}

