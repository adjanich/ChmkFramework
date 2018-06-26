#include "HexGrid.h"
#include <cmath>
#include <cassert>



HexGrid::Cell::Cell()
{
}

void HexGrid::Cell::Draw(Graphics & gfx)
{
	assert(Initiated);
	gfx.DrawLine(loc + Vec2<float>(0, -a), loc + Vec2<float>(0.5f*sqrtf(3)*a, -0.5f*a));
	gfx.DrawLine(loc + Vec2<float>(0, -a), loc + Vec2<float>(-0.5f*sqrtf(3)*a, -0.5f*a));
	gfx.DrawLine(loc + Vec2<float>(0, a), loc + Vec2<float>(0.5f*sqrtf(3)*a, 0.5f*a));
	gfx.DrawLine(loc + Vec2<float>(0, a), loc + Vec2<float>(-0.5f*sqrtf(3)*a, 0.5f*a));
	gfx.DrawLine(loc + Vec2<float>(0.5f*sqrtf(3)*a, 0.5f*a), loc + Vec2<float>(0.5f*sqrtf(3)*a, -0.5f*a));
	gfx.DrawLine(loc + Vec2<float>(-0.5f*sqrtf(3)*a, 0.5f*a), loc + Vec2<float>(-0.5f*sqrtf(3)*a, -0.5f*a));

}

void HexGrid::Cell::SetActive(bool in_Active)
{
	Active = in_Active;
}

bool HexGrid::Cell::IsActive() const
{
	return Active;
}

void HexGrid::Cell::SetLoc(const Vec2<float>& in_loc, float in_a)
{
	assert(in_loc.x >= 0.0f);
	assert(in_loc.y >= 0.0f);
	assert(in_loc.x < float(Graphics::ScreenWidth));
	assert(in_loc.y < float(Graphics::ScreenHeight));
	assert(in_a > 0);

	loc = in_loc;
	a = in_a;

	Initiated = true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

HexGrid::HexGrid(float a, int nRows, int nColumns, bool StartWithLonger, const RectI& rect)
	:
	HexGrid(a, nRows, nColumns, StartWithLonger, Vec2<float>(0.5f*(float(rect.Left() + rect.Right()) - GetWidth(a, nColumns)), 0.5f*(float(rect.Top() + rect.Bottom()) - GetHeight(a, nRows))))
{

}

HexGrid::HexGrid(float a, int nRows, int nColumns, bool StartWithLonger, const Vec2<float>& offset)
	:
	a(a),
	nRows(nRows),
	nColumns(nColumns),
	StartWithLonger(StartWithLonger),
	offset(offset)
{
	nCells = 0;
	for (int CurRow = 0; CurRow < nRows; CurRow++) {
		nCells += nCellsInRow(CurRow);
	}

	Cells = new Cell[nCells];

	int CurCell = 0;
	for (int CurRow = 0; CurRow < nRows; CurRow++) {
		for (int CurColumn = 0; CurColumn < nCellsInRow(CurRow); CurColumn++) {
			Cells[CurCell].SetLoc(offset + Vec2<float>((StartWithLonger ^ (CurRow % 2 == 0)) ? (sqrtf(3)*a*(1.0f + CurColumn)) : (sqrtf(3)*a*(0.5f + CurColumn)), (1.5f*CurRow + 1.0f)*a), a);
			CurCell++;
		}
	}

	Initiated = true;

}


HexGrid::~HexGrid()
{
	delete[] Cells;
}

void HexGrid::Draw(Graphics & gfx)
{
	for (int CurCell = 0; CurCell < nCells; CurCell++) {
		Cells[CurCell].Draw(gfx);
	}
}

float HexGrid::GetWidth() const
{
	assert(Initiated);
	return sqrtf(3)*a*float(nColumns);
}

float HexGrid::GetHeight() const
{
	assert(Initiated);
	return (1.5f*float(nRows) + 0.5f)*a;
}
float HexGrid::GetWidth(float a, int nColumns) const
{
	return sqrtf(3)*a*float(nColumns);
}

float HexGrid::GetHeight(float a, int nRows) const
{
	return (1.5f*float(nRows) + 0.5f)*a;
}

int HexGrid::nCellsInRow(int Row)
{
	assert(Row >= 0);
	assert(Row < nRows);

	if (StartWithLonger ^ (Row % 2 == 0)) {
		return (nColumns - 1);
	}
	else {
		return nColumns;
	}
}


