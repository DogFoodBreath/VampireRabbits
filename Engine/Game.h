/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "RabbitPen.h"
#include "Location.h"
#include "Rabbit.h"
#include "SpriteCodex.h"

#include <random>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	Location NewLocation(Rabbit& testrabbit);
	bool IsInPen(Location& loc, Location& next_loc, RabbitPen& pen);
	void Rabbit_Sortby_Age();
	const bool CellIsEmpty(const Location& rabbit,const Location& delta) const;
	void KillOldRabbits();
	void BreedingTest(Rabbit& testrabbit);
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	/********************************/
	RabbitPen rabbitpen;
	std::mt19937 rng;
	static constexpr int MaxRabbits = 1000;
	int number_of_rabbits = 100;
	int number_of_vampires = 0;
	int vampire_take_over;
	Rabbit rabbit[MaxRabbits];
	int maxAge = 25;
	bool isGameOver = false;
	SpriteCodex Sprite;
};