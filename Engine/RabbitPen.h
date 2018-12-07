#pragma once
#include "Location.h"
#include "Graphics.h"
class RabbitPen
{
public:
	RabbitPen(Graphics& gfx);
	void DrawPen(Location& loc, Color c);
	const int GetCellDimension() const;
	const int GetPenWidth() const;
	const int GetPenHeight() const;


private:

	Location loc;
	Graphics& gfx;

	static constexpr int PenWidth = 40;
	static constexpr int PenHeight = 40;
	static constexpr int CellDimension = 15;
};