#include "Rabbit.h"

Rabbit::Rabbit()
{
	loc.x = 20;
	loc.y = 20;
	age = 3;
	isVampire = false;
	isMale = true;
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