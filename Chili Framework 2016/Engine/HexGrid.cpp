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
void HexGrid::Cell::DrawSpecial(Graphics & gfx)
{
	assert(Initiated);
	gfx.DrawLine(loc + Vec2<float>(0, a), loc + Vec2<float>(0.5f*sqrtf(3)*a, -0.5f*a));
	gfx.DrawLine(loc + Vec2<float>(0, a), loc + Vec2<float>(-0.5f*sqrtf(3)*a, -0.5f*a));
	gfx.DrawLine(loc + Vec2<float>(0, -a), loc + Vec2<float>(0.5f*sqrtf(3)*a, 0.5f*a));
	gfx.DrawLine(loc + Vec2<float>(0, -a), loc + Vec2<float>(-0.5f*sqrtf(3)*a, 0.5f*a));
	gfx.DrawLine(loc + Vec2<float>(0.5f*sqrtf(3)*a, 0.5f*a), loc + Vec2<float>(-0.5f*sqrtf(3)*a, 0.5f*a));
	gfx.DrawLine(loc + Vec2<float>(0.5f*sqrtf(3)*a, -0.5f*a), loc + Vec2<float>(-0.5f*sqrtf(3)*a, -0.5f*a));

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



void HexGrid::Draw(Graphics & gfx, Vec2<float> MousePos)
{
	int HoverCelli=CelliFromVec(MousePos);

	for (int CurCell = 0; CurCell < nCells; CurCell++) {
		if (HoverCelli == CurCell) {
			Cells[CurCell].DrawSpecial(gfx);
		}
		else {
			Cells[CurCell].Draw(gfx);
		}
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

int HexGrid::nCellsInRow(int Row) const
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

////////////////////////////////////////////////////////////////////

int HexGrid::CelliFromVec(Vec2<float> vec) //const
{
	float x = (vec - offset).x;
	float y = (vec - offset).y;

	int Row;
	int Column;


	if (y < 0.0f) {
		return -1;
	}

	int Half_a_Multiple = int(2.0f*y / a);

	if (Half_a_Multiple % 3 == 0) { //zig_zag strip
		int MoreBottomRow = Half_a_Multiple / 3;
		int MoreUpperRow = Half_a_Multiple / 3 - 1;
		if (StartWithLonger ^ (MoreBottomRow % 2 == 0)) { //	\/\/\/...
			int HalfWidthsFromLeft = int(x / (0.5f*sqrtf(3)*a));
			if (HalfWidthsFromLeft % 2 == 0) {// \.
				const float FromTopInRect = y - MoreBottomRow * 1.5f*a;
				const float FromLeftInRect = x - 0.5f*sqrtf(3)*a*HalfWidthsFromLeft;
				if (FromTopInRect*sqrtf(3) > FromLeftInRect) { //Left/Bottom 
					Row = MoreBottomRow;
					Column = HalfWidthsFromLeft / 2 - 1;
				}
				else { //Right/Top
					Row = MoreUpperRow;
					Column = HalfWidthsFromLeft / 2;
				}
			}
			else {// /.
				const float FromBottomInRect = MoreBottomRow * 1.5f*a + 0.5f*a - y;
				const float FromLeftInRect = x - 0.5f*sqrtf(3)*a*HalfWidthsFromLeft;
				if (FromBottomInRect*sqrtf(3) > FromLeftInRect) { //Left/Top
					Row = MoreUpperRow;
					Column = HalfWidthsFromLeft / 2;
				}
				else { //Right/Bottom
					Row = MoreBottomRow;
					Column = HalfWidthsFromLeft / 2;
				}
			}
		}
		else{ //	/\/\/\...
			int HalfWidthsFromLeft = int(x / (0.5f*sqrtf(3)*a));
			if (HalfWidthsFromLeft % 2 == 0) {// /.
				const float FromBottomInRect = MoreBottomRow * 1.5f*a + 0.5f*a - y;
				const float FromLeftInRect = x - 0.5f*sqrtf(3)*a*HalfWidthsFromLeft;
				if (FromBottomInRect*sqrtf(3) > FromLeftInRect) { //Left/Top
					Row = MoreUpperRow;
					Column = HalfWidthsFromLeft / 2 - 1;
				}
				else { //Right/Bottom
					Row = MoreBottomRow;
					Column = HalfWidthsFromLeft / 2;
				}
			}
			else {// \.
				const float FromTopInRect = y - MoreBottomRow * 1.5f*a;
				const float FromLeftInRect = x - 0.5f*sqrtf(3)*a*HalfWidthsFromLeft;
				if (FromTopInRect*sqrtf(3) > FromLeftInRect) { //Left/Bottom 
					Row = MoreBottomRow;
					Column = HalfWidthsFromLeft / 2;
				}
				else { //Right/Top
					Row = MoreUpperRow;
					Column = HalfWidthsFromLeft / 2;
				}
			}
		}
	}
	else { // Cell_Centers strip
		Row = Half_a_Multiple / 3;
		if (Row >= nRows) { return -1; }
		if (StartWithLonger ^ (Row % 2 == 0)) { //shoter row
			if (x < 0.5f*sqrtf(3)*a) { return -1; }
			Column = int((x / (sqrtf(3)*a)) - 0.5f);
			if (Column >= nCellsInRow(Row)) { return -1; }
		}
		else { // longer row
			if (x < 0.0f) { return -1; }
			Column = int(x / (sqrtf(3)*a));
			if (Column >= nCellsInRow(Row)) { return -1; }
		}
	}

	if (Row < 0) { return -1; }
	if (Row >= nRows) { return -1; }
	if (Column < 0) { return -1; }
	if (Column >= nCellsInRow(Row)) { return -1; }
	return CelliFromRC(Row, Column);

}

int HexGrid::CelliFromRC(int Row, int Column) const
{
	assert(Initiated);
	assert(Row >= 0);
	assert(Row < nRows);
	assert(Column >= 0);
	assert(Column < nCellsInRow(Row));

	if (StartWithLonger) {
		if (Row % 2 == 0) {
			return (2 * nColumns - 1)*(Row / 2) + Column;
		}
		else {
			return (2 * nColumns - 1)*(Row / 2) + nColumns + Column;
		}
	}
	else {
		if (Row % 2 == 0) {
			return (2 * nColumns - 1)*(Row / 2) + Column;
		}
		else {
			return (2 * nColumns - 1)*(Row / 2) + nColumns - 1 + Column;
		}
	}
}

int HexGrid::RowFromCelli(int Celli)
{
	assert(Initiated);
//	assert(Celli >= 0);
//	assert(Celli < nCells);
	if (StartWithLonger) {
		if ((Celli % (2 * nColumns - 1)) < nColumns) {
			return 2 * (Celli / (2 * nColumns - 1));
		}
		else {
			return 2 * (Celli / (2 * nColumns - 1)) + 1;
		}
	}
	else {
		if ((Celli % (2 * nColumns - 1)) < nColumns - 1) {
			return 2 * (Celli / (2 * nColumns - 1));
		}
		else {
			return 2 * (Celli / (2 * nColumns - 1)) + 1;
		}
	}
}

int HexGrid::ColumnFromCelli(int Celli)
{
	assert(Initiated);
//	assert(Celli >= 0);
//	assert(Celli < nCells);
	if (StartWithLonger) {
		if ((Celli % (2 * nColumns - 1)) < nColumns) {
			return (Celli % (2 * nColumns - 1));
		}
		else {
			return (Celli % (2 * nColumns - 1)) - nColumns;
		}
	}
	else {
		if ((Celli % (2 * nColumns - 1)) < nColumns-1) {
			return (Celli % (2 * nColumns - 1));
		}
		else {
			return (Celli % (2 * nColumns - 1)) - (nColumns - 1);
		}
	}
}

