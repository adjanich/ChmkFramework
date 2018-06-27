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
void HexGrid::Cell::DrawHover(Graphics & gfx)
{

	assert(Initiated);

	const Color c = Color(100, 100, 100);
	
	for (float i = 0.0f; i < 1.7f; i += 0.5f) {
		gfx.DrawLine(loc + Vec2<float>(0, -a + i * 1.5f), loc + Vec2<float>(0.5f*sqrtf(3)*a - i, -0.5f*a + i), c);
		gfx.DrawLine(loc + Vec2<float>(0, -a + i * 1.5f), loc + Vec2<float>(-0.5f*sqrtf(3)*a + i, -0.5f*a + i), c);
		gfx.DrawLine(loc + Vec2<float>(0, a - i * 1.5f), loc + Vec2<float>(0.5f*sqrtf(3)*a - i, 0.5f*a - i), c);
		gfx.DrawLine(loc + Vec2<float>(0, a - i * 1.5f), loc + Vec2<float>(-0.5f*sqrtf(3)*a + i, 0.5f*a - i), c);
		gfx.DrawLine(loc + Vec2<float>(0.5f*sqrtf(3)*a - i, 0.5f*a - i), loc + Vec2<float>(0.5f*sqrtf(3)*a - i, -0.5f*a + i), c);
		gfx.DrawLine(loc + Vec2<float>(-0.5f*sqrtf(3)*a + i, 0.5f*a - i), loc + Vec2<float>(-0.5f*sqrtf(3)*a + i, -0.5f*a + i), c);
	}
	Draw(gfx);
}
void HexGrid::Cell::DrawSideHover(Graphics & gfx, int side)
{
	assert(Initiated);
	if (side == -1) { return; }
	assert(side >= 0);
	assert(side < 6);

	const Color c = Color(100, 255, 100);
	const Vec2<float> shifts[4] = {
		Vec2<float>(0.0f,1.0f),
		Vec2<float>(0.0f,-1.0f),
		Vec2<float>(1.0f,0.0f),
		Vec2<float>(-1.0f,0.0f)
	};

	for (int i = 0; i < 4; i++) {
		switch (side) {
		case 0:
			gfx.DrawLine(loc + shifts[i] + Vec2<float>(0, -a), loc + shifts[i] + Vec2<float>(0.5f*sqrtf(3)*a, -0.5f*a), c);
			break;
		case 1:
			gfx.DrawLine(loc + shifts[i] + Vec2<float>(0.5f*sqrtf(3)*a, 0.5f*a), loc + shifts[i] + Vec2<float>(0.5f*sqrtf(3)*a, -0.5f*a), c);
			break;
		case 2:
			gfx.DrawLine(loc + shifts[i] + Vec2<float>(0, a), loc + shifts[i] + Vec2<float>(0.5f*sqrtf(3)*a, 0.5f*a), c);
			break;
		case 3:
			gfx.DrawLine(loc + shifts[i] + Vec2<float>(0, a), loc + shifts[i] + Vec2<float>(-0.5f*sqrtf(3)*a, 0.5f*a), c);
			break;
		case 4:
			gfx.DrawLine(loc + shifts[i] + Vec2<float>(-0.5f*sqrtf(3)*a, 0.5f*a), loc + shifts[i] + Vec2<float>(-0.5f*sqrtf(3)*a, -0.5f*a), c);
			break;
		case 5:
			gfx.DrawLine(loc + shifts[i] + Vec2<float>(0, -a), loc + shifts[i] + Vec2<float>(-0.5f*sqrtf(3)*a, -0.5f*a), c);
			break;

		default:
			assert(false);
		}
	}

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

	Initiated = true;

	Cells = new Cell[nCells];

	for (int Celli = 0; Celli < nCells; Celli++) {
			Cells[Celli].SetLoc(VecCenter(Celli), a);
	}



}


HexGrid::~HexGrid()
{
	delete[] Cells;
}



void HexGrid::Draw(Graphics & gfx, Vec2<float> MousePos)
{
	int HoverCelli=CelliFromVec(MousePos);


	if (HoverCelli != -1) {
//		Cells[HoverCelli].DrawHover(gfx);
		Cells[HoverCelli].DrawSideHover(gfx, SectorFromVec(MousePos));
	}

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

int HexGrid::CelliFromVec(Vec2<float> vec) const
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

int HexGrid::RowFromCelli(int Celli) const
{
	assert(Initiated);
	assert(Celli >= 0);
	assert(Celli < nCells);
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

int HexGrid::ColumnFromCelli(int Celli) const
{
	assert(Initiated);
	assert(Celli >= 0);
	assert(Celli < nCells);
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

Vec2<float> HexGrid::VecCenter(int Celli) const
{
	return VecCenter(RowFromCelli(Celli), ColumnFromCelli(Celli));
}

Vec2<float> HexGrid::VecCenter(int Row, int Column) const
{
	return offset + Vec2<float>((StartWithLonger ^ (Row % 2 == 0)) ? (sqrtf(3)*a*(1.0f + Column)) : (sqrtf(3)*a*(0.5f + Column)), (1.5f*Row + 1.0f)*a);
}

Vec2<float> HexGrid::VecCorner(int Celli, int Corneri) const
{
	assert(Corneri >= 0);
	assert(Corneri < 6);
	switch (Corneri) {
	case 0:
		return VecCenter(Celli) + Vec2<float>(0, -a);
	case 1:
		return VecCenter(Celli) + Vec2<float>(0.5f*sqrtf(3)*a, -0.5f*a);
	case 2:
		return VecCenter(Celli) + Vec2<float>(0.5f*sqrtf(3)*a, 0.5f*a);
	case 3:
		return VecCenter(Celli) + Vec2<float>(0, a);
	case 4:
		return VecCenter(Celli) + Vec2<float>(-0.5f*sqrtf(3)*a, 0.5f*a);
	case 5:
		return VecCenter(Celli) + Vec2<float>(-0.5f*sqrtf(3)*a, -0.5f*a);
	default:
		assert(false);
		return Vec2<float>(0.0f, 0.0f);
	}
}

Vec2<float> HexGrid::VecCorner(int Row, int Column, int Corneri) const
{
	assert(Corneri >= 0);
	assert(Corneri < 6);
	switch (Corneri) {
	case 0:
		return VecCenter(Row, Column) + Vec2<float>(0, -a);
	case 1:
		return VecCenter(Row, Column) + Vec2<float>(0.5f*sqrtf(3)*a, -0.5f*a);
	case 2:
		return VecCenter(Row, Column) + Vec2<float>(0.5f*sqrtf(3)*a, 0.5f*a);
	case 3:
		return VecCenter(Row, Column) + Vec2<float>(0, a);
	case 4:
		return VecCenter(Row, Column) + Vec2<float>(-0.5f*sqrtf(3)*a, 0.5f*a);
	case 5:
		return VecCenter(Row, Column) + Vec2<float>(-0.5f*sqrtf(3)*a, -0.5f*a);
	default:
		assert(false);
		return Vec2<float>(0.0f, 0.0f);
	}
}

int HexGrid::SectorFromVec(Vec2<float> vec) const
{
	if (CelliFromVec(vec) == -1) { 
		return -1; 
	}
	const Vec2<float> shift = VecCenter(CelliFromVec(vec)) - vec;
	return int(3.0f*(atan2f(shift.y, shift.x)) / PI + 10.5f) % 6;
}

int HexGrid::AdjacentCelli(int Celli, int Dir)
{
	
	assert(Initiated);

	if (Dir == -1) { return -1; }

	assert(Dir >= 0);
	assert(Dir < 6);

	if (Celli == -1) { return -1; }

	assert(Celli >= 0);
	assert(Celli < nCells);


	int Row = RowFromCelli(Celli);
	int Column = ColumnFromCelli(Celli);

	switch (Dir) {
	case 0:
		if (StartWithLonger ^ (Row % 2 == 0)) {
			Column++;
		}
		Row--;
		break;
	case 1:
		Column++;
		break;
	case 2:
		if (StartWithLonger ^ (Row % 2 == 0)) {
			Column++;
		}
		Row++;
		break;
	case 3:
		if (StartWithLonger ^ (Row % 2 == 1)) {
			Column--;
		}
		Row++;
		break;
	case 4:
		Column--;
		break;
	case 5:
		if (StartWithLonger ^ (Row % 2 == 1)) {
			Column--;
		}
		Row--;
		break;
	default:
		assert(false);
	}

	if (Row < 0) { return -1; }
	if (Row >= nRows) { return -1; }
	if (Column < 0) { return -1; }
	if (Column >= nCellsInRow(Row)) { return -1; }

	return CelliFromRC(Row, Column);
}

