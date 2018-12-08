#include "RabbitPen.h"

RabbitPen::RabbitPen(Graphics & gfx)
	:
	gfx ( gfx )
{
}

void RabbitPen::DrawPen(Location & loc, Color c)
{
	gfx.DrawRectDim(loc.x*CellDimension, loc.y*CellDimension, CellDimension, CellDimension, c);
}

const int RabbitPen::GetCellDimension()
{
	return CellDimension;
}

const int RabbitPen::GetPenWidth()
{
	return PenWidth;
}
const int RabbitPen::GetPenHeight()
{
	return PenHeight;
}
