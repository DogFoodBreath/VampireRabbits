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

const int RabbitPen::GetCellDimension() const
{
	return CellDimension;
}

const int RabbitPen::GetPenWidth() const
{
	return PenWidth;
}
const int RabbitPen::GetPenHeight() const
{
	return PenHeight;
}
