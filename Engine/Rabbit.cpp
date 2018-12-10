#include "Rabbit.h"
#include <ctime>

Rabbit::Rabbit()
{
	/*isMale = true;
	isVampire = false;
	loc.x = 20;
	loc.y = 20;
	age = 1;*/

	std::default_random_engine rd(time(NULL));
	//std::mt19937 rng(rd());
	std::uniform_int_distribution<int> gender(1, 100);
	if (gender(rd) >= 50)
	{
		isMale = true;
	}
	else isMale = false;
	std::uniform_int_distribution<int> xdist(1, RabbitPen::GetPenWidth());
	std::uniform_int_distribution<int> ydist(1, RabbitPen::GetPenHeight());
	loc.x = xdist(rd);
	loc.y = ydist(rd);
	age = 0;
	if (gender(rd) <= 5)
	{
		isVampire = true;
	}
	else isVampire = false;

	isdead = false;
}


Rabbit::Rabbit(Location& momloc)
{
	loc.x = momloc.x + 1;
	loc.y = momloc.y;
	std::mt19937 rng(time(0));
	std::uniform_int_distribution<int> gender(1, 100);
	if (gender(rng) >= 50)
	{
		isMale = true;
	}
	else isMale = false;
	if (gender(rng) <= 5)
	{
		isVampire = true;
	}
	else isVampire = false;

	isdead = false;
}



  ///////////////////////////////////////////
 /*           Getter Functions           */
//////////////////////////////////////////
const bool Rabbit::GetGender() const 
{
	return isMale;
}

const bool Rabbit::IsInfected() const 
{
	return isVampire;
}

const int Rabbit::getAge() const
{
	return age;
}
const Location Rabbit::GetLoc() const
{
	return loc;
}




void Rabbit::DrawBunny(RabbitPen & rabbitpen)
{
	if (isVampire)
	{
		rabbitpen.DrawPen(loc, Colors::Red);
	}
	else if (isMale)
	{
		if (age <= 2)
		{
			rabbitpen.DrawPen(loc, Colors::MakeRGB(125, 225, 255));
		}
		else
		{
			rabbitpen.DrawPen(loc, Colors::Blue);
		}
	}
	else
	{
		if (age <= 2)
		{
			rabbitpen.DrawPen(loc, Colors::MakeRGB(255, 125, 225));
		}
		else
		{
		rabbitpen.DrawPen(loc, Colors::Magenta);
		}
	}
}

void Rabbit::Move(Location& new_loc)
{
	
	loc.x += new_loc.x;
	loc.y += new_loc.y;
	
}

void Rabbit::isDead()
{
	if (age > 10)
	{
		isdead = true;
	}
	else
	{
		isdead = false;
	}

}