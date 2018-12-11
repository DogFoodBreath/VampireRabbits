#include "Rabbit.h"
#include <ctime>

Rabbit::Rabbit()
{

}

void Rabbit::RabbitInitial(std::mt19937& rng) 
{


	std::uniform_int_distribution<int> gender(1, 100);
	std::uniform_int_distribution<int> vampDist(1, 100);
	int rnInt = gender(rng);
	if (rnInt >= 50)
	{
		isMale = true;
	}
	else isMale = false;
	std::uniform_int_distribution<int> xdist(1, RabbitPen::GetPenWidth());
	std::uniform_int_distribution<int> ydist(1, RabbitPen::GetPenHeight());
	loc.x = xdist(rng);
	loc.y = ydist(rng);
	age = 0;
	int rnIntVamp = vampDist(rng);
	if ( rnIntVamp <= 5)
	{
		isVampire = true;
	}
	else isVampire = false;

	isdead = false;
}


Rabbit::Rabbit(Location& momloc, std::mt19937& rng)
{
	loc.x = momloc.x + 1;
	loc.y = momloc.y;

	std::uniform_int_distribution<int> gender(1, 100);
	std::uniform_int_distribution<int> isVamp(1, 100);

	if (gender(rng) >= 50)
	{
		isMale = true;
	}
	else isMale = false;
	if (isVamp(rng) <= 5)
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

void Rabbit::KillTheRabbit()
{
	age = 1000;
}

void Rabbit::RabbitAgeIncrementer()
{
	age += 1;
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