#pragma once


class Location
{
public:
	Location& GetLocation(Location& loc)
	{
		return loc;
	}
	bool operator==(const Location& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
	int x;
	int y;
};