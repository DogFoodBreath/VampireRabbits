#pragma once


class Location
{
public:
	Location& GetLocation(Location& loc)
	{
		return loc;
	}
	bool Location::operator==(const Location& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
	bool Location::operator!=(const Location& rhs) const
	{
		return x != rhs.x || y != rhs.y;
	}
	Location& Location::operator=(const Location& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}
	Location& Location::operator+(const Location& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	int x;
	int y;
};