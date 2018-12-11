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
	for (int i = 0; i < number_of_rabbits; i++)
	{
		rabbit[i].RabbitInitial(rng);
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
	Sleep(1000);
}

void Game::UpdateModel()
{
	Rabbit_Sortby_Age();
	for (int i = 0; i < number_of_rabbits; i++)
	{
		Location newloc = NewLocation(i);
		if (CellIsEmpty(rabbit[i].GetLoc(), newloc))
		{
		rabbit[i].Move(NewLocation(i));
		}
	}
	RabbitAgeIncrementer();
}

void Game::ComposeFrame()
{
	std::uniform_int_distribution<int> cdist(0, 255);
	Location loc = { 20,20 };
	for (int i = 0; i < number_of_rabbits; i++)
	{
		rabbit[i].DrawBunny(rabbitpen);
	}
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
	default:
		nextloc = { 0,0 };
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

void Game::Rabbit_Sortby_Age()
{
	Rabbit temprabbit;
	for (int j = 0; j < number_of_rabbits; j++)
	{
		for (int i = 0; i < number_of_rabbits; i++)
		{
			if (rabbit[i].getAge() > rabbit[i + 1].getAge())
			{
				temprabbit = rabbit[i];
				rabbit[i] = rabbit[2];
				rabbit[2] = temprabbit;
			
			}
		}

	}
}

void Game::RabbitAgeIncrementer()
{
	for (int i = 0; i < number_of_rabbits; i++)
	{
		rabbit[i].RabbitAgeIncrementer();
		if (rabbit[i].getAge() > 10 && !rabbit[i].IsInfected())
		{
			rabbit[i].KillTheRabbit();
			number_of_rabbits -= 1;
		}
		else if (rabbit[i].getAge() > 50)
		{
			rabbit[i].KillTheRabbit();
			number_of_rabbits -= 1;
		}
	}

}

const bool Game::CellIsEmpty(const Location& rabbitloc,const Location& deltaloc) const
{
	Location newlocation = { rabbitloc.x + deltaloc.x, rabbitloc.y + deltaloc.y };
	for (int i = 0; i < number_of_rabbits; i++)
	{
		if (rabbit[i].GetLoc() == newlocation)
		{
			return false;
		}
	}
	return true;

}

const bool Game::BreedingTest(Rabbit& testrabbit) const
{
	for (int i = 0; i < number_of_rabbits; i++)
	{
		if ((testrabbit.GetLoc().x + 1 == rabbit[i].GetLoc().x && testrabbit.GetLoc().y == rabbit[i].GetLoc().y) ||
			(testrabbit.GetLoc().x - 1 == rabbit[i].GetLoc().x && testrabbit.GetLoc().y == rabbit[i].GetLoc().y) ||
			(testrabbit.GetLoc().x == rabbit[i].GetLoc().x && testrabbit.GetLoc().y + 1 == rabbit[i].GetLoc().y) ||
			(testrabbit.GetLoc().x == rabbit[i].GetLoc().x && testrabbit.GetLoc().y - 1 == rabbit[i].GetLoc().y))
		{
			if (testrabbit.GetGender() != rabbit[i].GetGender() )
			{
				return true;
			}
		}
	}
	return false;
}
