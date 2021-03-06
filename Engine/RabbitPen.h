#pragma once
#include "Location.h"
#include "Graphics.h"
class RabbitPen
{
public:
	RabbitPen(Graphics& gfx);
	void DrawPen(Location& loc, Color c);
	static const int GetCellDimension();
	static const int GetPenWidth();
	static const int GetPenHeight();


private:

	Location loc;
	Graphics& gfx;

	static constexpr int PenWidth = 79;
	static constexpr int PenHeight = 59;
	static constexpr int CellDimension = 10;
};