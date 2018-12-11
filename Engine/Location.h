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
	Location Location::operator=(const Location& rhs) const
	{
		Location lhs;
		lhs.x = rhs.x;
		lhs.y = rhs.y;
		return lhs;
	}
	int x;
	int y;
};