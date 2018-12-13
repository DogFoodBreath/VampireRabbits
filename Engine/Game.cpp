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
#include "SpriteCodex.h"


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
		if (rabbit[i].IsInfected())
		{
			number_of_vampires++;
		}
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
	if (!isGameOver)
	{

		for (int i = 0; i < number_of_rabbits; i++)
		{
			BreedingTest(rabbit[i]);
			Location newloc = NewLocation(rabbit[i]);
			if (CellIsEmpty(rabbit[i].GetLoc(), newloc))
			{
				rabbit[i].Move(newloc);
			}
			rabbit[i].ResetForBreeding();
			rabbit[i].RabbitAgeIncrementer();
		}
		KillOldRabbits();
	}
	vampire_take_over = number_of_rabbits - number_of_vampires;
	if (number_of_rabbits <= 0 || number_of_rabbits == number_of_vampires)
	{
		isGameOver = true;
	}

}

void Game::ComposeFrame()
{
	if (!isGameOver)
	{	
		for (int i = 0; i < number_of_rabbits; i++)
		{
			rabbit[i].DrawBunny(rabbitpen);
		}
	}
	else SpriteCodex::DrawGameOver(350,300,gfx);
}













Location Game::NewLocation(Rabbit& testrabbit)
{
	Location nextloc, locholder;
	locholder = testrabbit.GetLoc();
	std::uniform_int_distribution<int> newloc(1, 4);
	switch (newloc(rng))
	{
	case (1):
		nextloc.x = -1;
		nextloc.y = 0;
		if (!IsInPen(locholder, nextloc, rabbitpen))
		{
			nextloc.x = 0;
			nextloc.y = 0;
		}
		return nextloc;
		break;
	case (2):
		nextloc.x = 1;
		nextloc.y = 0;
		if (!IsInPen(locholder, nextloc, rabbitpen))
		{
			nextloc.x = 0;
			nextloc.y = 0;
		}
		return nextloc;
		break;
	case (3):
		nextloc.x = 0;
		nextloc.y = -1;
		if (!IsInPen(locholder, nextloc, rabbitpen))
		{
			nextloc.x = 0;
			nextloc.y = 0;
		}
		return nextloc;
		break;
	case (4):
		nextloc.x = 0;
		nextloc.y = 1;
		if (!IsInPen(locholder, nextloc, rabbitpen))
		{			
			nextloc.x = 0;
			nextloc.y = 0;
		}
		return nextloc;
		break;
	default:
		nextloc.x = 0;
		nextloc.y = 0;
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
	for (int j = 0; j < number_of_rabbits; j++)
	{
		for (int i = 0; i < number_of_rabbits-1; i++)
		{
			if (rabbit[i].getAge() > rabbit[i + 1].getAge())
			{
				std::swap(rabbit[i], rabbit[i + 1]);
			}
		}

	}
}

void Game::KillOldRabbits()
{
	int deadRabbitCounter = 0;
	for (int i = 0; i < number_of_rabbits; i++)
	{
		if (rabbit[i].getAge() > maxAge && !rabbit[i].IsInfected())
		{
			rabbit[i].KillTheRabbit();
			deadRabbitCounter++;
		}
		else if (rabbit[i].getAge() > 50 && rabbit[i].IsInfected())
		{
			rabbit[i].KillTheRabbit();
			deadRabbitCounter++;
			number_of_vampires--;
		}
	}
	Rabbit_Sortby_Age();
	number_of_rabbits -= deadRabbitCounter;

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

void Game::BreedingTest(Rabbit& testrabbit) 
{
	for (int i = 0; i < number_of_rabbits; i++)
	{
			if ((testrabbit.GetLoc().x + 1 == rabbit[i].GetLoc().x && testrabbit.GetLoc().y == rabbit[i].GetLoc().y) ||
				(testrabbit.GetLoc().x - 1 == rabbit[i].GetLoc().x && testrabbit.GetLoc().y == rabbit[i].GetLoc().y) ||
				(testrabbit.GetLoc().x == rabbit[i].GetLoc().x && testrabbit.GetLoc().y + 1 == rabbit[i].GetLoc().y) ||
				(testrabbit.GetLoc().x == rabbit[i].GetLoc().x && testrabbit.GetLoc().y - 1 == rabbit[i].GetLoc().y))
			{
				if (testrabbit.IsInfected() && !rabbit[i].IsInfected())
				{
					rabbit[i].GetInfected();
					number_of_vampires++;
				}
				else if ( (testrabbit.GetGender() != rabbit[i].GetGender() ) && 
						  (testrabbit.getAge() > 2 && rabbit[i].getAge() > 2) )
					 {
						if ( !testrabbit.GetGender() && !testrabbit.DidSheBreed())
						{
							Location newlocation = NewLocation(testrabbit);
							Location testrabbitloc = testrabbit.GetLoc();
							if (IsInPen(testrabbitloc, newlocation, rabbitpen) && CellIsEmpty(testrabbit.GetLoc(), newlocation))
							{
								Rabbit(newlocation, testrabbit, rabbit[number_of_rabbits], rng);
								if (rabbit[number_of_rabbits].IsInfected())
								{
									number_of_vampires++;
								}
								number_of_rabbits++;
							}
						}
						else if (!rabbit[i].DidSheBreed())
						{
							Location newlocation = NewLocation(rabbit[i]);
							Location testrabbitloc = rabbit[i].GetLoc();
							if (IsInPen(testrabbitloc, newlocation, rabbitpen) && CellIsEmpty(rabbit[i].GetLoc(), newlocation))
							{
								Rabbit(newlocation, rabbit[i], rabbit[number_of_rabbits], rng);
								if (rabbit[number_of_rabbits].IsInfected())
								{
									number_of_vampires++;
								}
								number_of_rabbits++;
							}
							
						}
					
					 }
			}
	}
}
