#include "HexGrid.h"
#include <cmath>
#include <cassert>



HexGrid::Cell::Cell()
{
}


void HexGrid::Cell::DrawHover(Graphics & gfx, Color Trench)
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
	DrawBorder(gfx, Trench);
}
void HexGrid::Cell::DrawSideHover(Graphics & gfx, int side, Color Out, Color Trench)
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

void HexGrid::Cell::SwitchConnection(int Side)
{
	if (Side >= 0 && Side < 6) {
		HasConnection[Side] = !HasConnection[Side];
	}
}

void HexGrid::Cell::Rot()
{
	const bool buf = HasConnection[5];
	HasConnection[5] = HasConnection[4];
	HasConnection[4] = HasConnection[3];
	HasConnection[3] = HasConnection[2];
	HasConnection[2] = HasConnection[1];
	HasConnection[1] = HasConnection[0];
	HasConnection[0] = buf;
}

void HexGrid::Cell::DrawBorder(Graphics & gfx, Color Trench)
{
	assert(Initiated);
	if (HasConnection[0]) {
		DrawInteruptedLine(gfx, loc + Vec2<float>(0, -a), loc + Vec2<float>(0.5f*sqrtf(3)*a, -0.5f*a),Trench);
	}
	else {
		gfx.DrawLine(loc + Vec2<float>(0, -a), loc + Vec2<float>(0.5f*sqrtf(3)*a, -0.5f*a));
	}
	if (HasConnection[1]) {
		DrawInteruptedLine(gfx, loc + Vec2<float>(0.5f*sqrtf(3)*a, 0.5f*a), loc + Vec2<float>(0.5f*sqrtf(3)*a, -0.5f*a), Trench);
	}
	else {
		gfx.DrawLine(loc + Vec2<float>(0.5f*sqrtf(3)*a, 0.5f*a), loc + Vec2<float>(0.5f*sqrtf(3)*a, -0.5f*a));
	}
	if (HasConnection[2]) {
		DrawInteruptedLine(gfx, loc + Vec2<float>(0, a), loc + Vec2<float>(0.5f*sqrtf(3)*a, 0.5f*a), Trench);
	}
	else {
		gfx.DrawLine(loc + Vec2<float>(0, a), loc + Vec2<float>(0.5f*sqrtf(3)*a, 0.5f*a));
	}
	if (HasConnection[3]) {
		DrawInteruptedLine(gfx, loc + Vec2<float>(0, a), loc + Vec2<float>(-0.5f*sqrtf(3)*a, 0.5f*a), Trench);
	}
	else {
		gfx.DrawLine(loc + Vec2<float>(0, a), loc + Vec2<float>(-0.5f*sqrtf(3)*a, 0.5f*a));
	}
	if (HasConnection[4]) {
		DrawInteruptedLine(gfx, loc + Vec2<float>(-0.5f*sqrtf(3)*a, 0.5f*a), loc + Vec2<float>(-0.5f*sqrtf(3)*a, -0.5f*a), Trench);
	}
	else {
		gfx.DrawLine(loc + Vec2<float>(-0.5f*sqrtf(3)*a, 0.5f*a), loc + Vec2<float>(-0.5f*sqrtf(3)*a, -0.5f*a));
	}
	if (HasConnection[5]) {
		DrawInteruptedLine(gfx, loc + Vec2<float>(0, -a), loc + Vec2<float>(-0.5f*sqrtf(3)*a, -0.5f*a), Trench);
	}
	else {
		gfx.DrawLine(loc + Vec2<float>(0, -a), loc + Vec2<float>(-0.5f*sqrtf(3)*a, -0.5f*a));
	}



}
void HexGrid::Cell::DrawBackground(Graphics & gfx, Color Out, Color Trench)
{
	const int CenterX = int(loc.x);
	const int CenterY = int(loc.y);
	const int iMax = int(sqrtf(3)*0.5f*a);

	int CellType = 0;
	for (int Digit = 0; Digit < 6; Digit++) {
		CellType *= 2;
		if (HasConnection[Digit]) {
			CellType++;
		}
	}

	int CurPx = CellType*PxPerCell;
	for (int i = 0; i <= iMax; i++) {
		const int jMin = -int(a - float(i) / sqrtf(3));
		const int jMax = int(a-float(i)/sqrtf(3));
		for (int j = jMin; j <= jMax; j++) {
			gfx.PutPixel(CenterX + i, CenterY + j, Pixels[CurPx]);
			CurPx++;
			gfx.PutPixel(CenterX - i, CenterY + j, Pixels[CurPx]);
			CurPx++;
		}
	}

}
void HexGrid::Cell::DrawInteruptedLine(Graphics & gfx, Vec2<float> v1, Vec2<float> v2, Color Trench, Color BorderColor)
{
	
	const float Lenght = sqrtf(((v2 - v1).x)*((v2 - v1).x) + ((v2 - v1).y)*((v2 - v1).y));
	for (float d = 0; d <= Lenght * SideFraction; d += 1.0f) {
		gfx.PutPixel(int(d*(v2.x - v1.x) / Lenght + v1.x), int(d*(v2.y - v1.y) / Lenght + v1.y), BorderColor);
	}
	for (float d = Lenght * (1 - SideFraction); d <= Lenght; d += 1.0f) {
		gfx.PutPixel(int(d*(v2.x - v1.x) / Lenght + v1.x), int(d*(v2.y - v1.y) / Lenght + v1.y), BorderColor);
	}
	for (float d = Lenght * SideFraction; d <= Lenght * (1 - SideFraction); d += 1.0f) {
		gfx.PutPixel(int(d*(v2.x - v1.x) / Lenght + v1.x), int(d*(v2.y - v1.y) / Lenght + v1.y), Trench);
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
void HexGrid::Cell::Initiate(const Vec2<float>& in_loc, float in_a, Color* in_Pixels, int in_PxPerCell)
{
	assert(in_loc.x >= 0.0f);
	assert(in_loc.y >= 0.0f);
	assert(in_loc.x < float(Graphics::ScreenWidth));
	assert(in_loc.y < float(Graphics::ScreenHeight));
	assert(in_a > 0);

	loc = in_loc;
	a = in_a;

	Pixels = in_Pixels;
	PxPerCell = in_PxPerCell;

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

	InitiatePixels(Color(100, 100, 0), Color(0, 0, 255));

	for (int Celli = 0; Celli < nCells; Celli++) {
			Cells[Celli].Initiate(VecCenter(Celli), a, Pixels, PxPerCell);
	}



}


HexGrid::~HexGrid()
{
	delete[] Cells;
}

void HexGrid::AddOrRemoveConnection(Vec2<float> MousePos)
{
	const int Celli = CelliFromVec(MousePos);
	const int Sector = SectorFromVec(MousePos);
	if (Celli != -1) {
		Cells[Celli].SwitchConnection(Sector);
		const int AdjCelli = AdjacentCelli(Celli, Sector);
		if (AdjCelli != -1) {
			Cells[AdjCelli].SwitchConnection((Sector + 3) % 6);
		}
	}
	
}
void HexGrid::Rot(Vec2<float> MousePos)
{
	const int Celli = CelliFromVec(MousePos);
	if (Celli != -1) {
		Cells[Celli].Rot();
	}
}



void HexGrid::Draw(Graphics & gfx, Vec2<float> MousePos)
{
	for (int CurCell = 0; CurCell < nCells; CurCell++) {
		Cells[CurCell].DrawBackground(gfx, Color(100, 100, 0), Color(0, 0, 255));
	}

	for (int CurCell = 0; CurCell < nCells; CurCell++) {
		Cells[CurCell].DrawBorder(gfx, Color(0, 0, 255));
	}
}
void HexGrid::DrawHover(Graphics & gfx, Vec2<float> MousePos)
{
	int HoverCelli = CelliFromVec(MousePos);

	for (int CurCell = 0; CurCell < nCells; CurCell++) {
		Cells[CurCell].DrawBackground(gfx, Color(100, 100, 0), Color(0, 0, 255));
	}

	if (HoverCelli != -1) {
		Cells[HoverCelli].DrawHover(gfx,Color(0,0,255));
	}

	for (int CurCell = 0; CurCell < nCells; CurCell++) {
		Cells[CurCell].DrawBorder(gfx, Color(0, 0, 255));
	}
}
void HexGrid::DrawSideHover(Graphics & gfx, Vec2<float> MousePos)
{
	int HoverCelli = CelliFromVec(MousePos);

	for (int CurCell = 0; CurCell < nCells; CurCell++) {
		Cells[CurCell].DrawBackground(gfx, Color(100, 100, 0), Color(0, 0, 255));
	}

	if (HoverCelli != -1) {
		Cells[HoverCelli].DrawSideHover(gfx, SectorFromVec(MousePos), Color(100, 100, 0), Color(0, 0, 255));
	}

	for (int CurCell = 0; CurCell < nCells; CurCell++) {
		Cells[CurCell].DrawBorder(gfx, Color(0, 0, 255));
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

void HexGrid::InitiatePixels(Color Out, Color Trench)
{
	assert(a > 0.0f);
	assert(a < 500.0f);
	assert(nCells > 0);
	assert(nCells < 500);


	PxPerCell = 0;
	const int iMax = int(sqrtf(3)*0.5f*a);

	for (int i = 0; i <= iMax; i++) {
		const int jMin = -int(a - float(i) / sqrtf(3));
		const int jMax = int(a - float(i) / sqrtf(3));
		for (int j = jMin; j <= jMax; j++) {
			PxPerCell += 2;
		}
	}

	Pixels = new Color[PxPerCell * 64];

	bool Connection[6] = { false, false, false, false, false, false };

	int CurPx = 0;
	for (int CellType = 0; CellType < 64; CellType++) {
		
		///////////////////////////// nConnections
		int nConnections = 0;
		for (int CurSide = 0; CurSide < 6; CurSide++) {
			if (Connection[CurSide]) {
				nConnections++;
			}
		}

		if (nConnections == 0) {
			for (int i = 0; i <= iMax; i++) {
				const int jMin = -int(a - float(i) / sqrtf(3));
				const int jMax = int(a - float(i) / sqrtf(3));
				for (int j = jMin; j <= jMax; j++) {
					Pixels[CurPx] = Out;
					CurPx++;
					Pixels[CurPx] = Out;
					CurPx++;
				}
			}
		}
		else {
			int From[6];
			int To[6];

			int CurPath = 0;
			for (int CurSide = 0; CurSide < 6; CurSide++) {
				if (Connection[CurSide]) {
					From[CurPath] = CurSide;
					To[(CurPath - 1 + nConnections) % nConnections] = CurSide;
					CurPath++;
				}
			}

			for (int i = 0; i <= iMax; i++) {
				const int jMin = -int(a - float(i) / sqrtf(3));
				const int jMax = int(a - float(i) / sqrtf(3));
				for (int j = jMin; j <= jMax; j++) {
					Pixels[CurPx] = TrenchColorGradient(Out, Trench, InTrench(float(i), float(j), nConnections, From, To));
					CurPx++;
					Pixels[CurPx] = TrenchColorGradient(Out, Trench, InTrench(float(-i), float(j), nConnections, From, To));
					CurPx++;
				}
			}
		}
	
	
	
		//////////////////////////////////// next binary number
		if (CellType < 63) {
			int Digit = 5;
			while (Connection[Digit]) {
				Connection[Digit] = false;
				Digit--;
			}
			if (Digit >= 0) { Connection[Digit] = true; }
		}
	}
}
float HexGrid::InTrench(float i, float j, int nConnections, int* From, int* To) const
{

	assert(abs(i) <= sqrtf(3)*0.5f*a + 1.0f);
	assert(abs(j) <= a + 1.0f);


	const float SideFraction = Cell::SideFraction;


	for (int CurPath = 0; CurPath < nConnections; CurPath++) {
		float r;

		switch ((To[CurPath] - From[CurPath] + 6) % 6) {
		case 0: // dif=0;
			r = (0.5f - SideFraction)*a;
			switch (From[CurPath]) {
			case 0:
				if ((i - 0.25f*sqrtf(3)*a)*(i - 0.25f*sqrtf(3)*a) + (j + 0.75f*a)*(j + 0.75f*a) > r*r) {
					return sqrtf((i - 0.25f*sqrtf(3)*a)*(i - 0.25f*sqrtf(3)*a) + (j + 0.75f*a)*(j + 0.75f*a)) - r;
				}
				break;
			case 1:
				if ((i - 0.5f*sqrtf(3)*a)*(i - 0.5f*sqrtf(3)*a) + j * j > r*r) {
					return sqrtf((i - 0.5f*sqrtf(3)*a)*(i - 0.5f*sqrtf(3)*a) + j * j) - r;
				}
				break;
			case 2:
				if ((i - 0.25f*sqrtf(3)*a)*(i - 0.25f*sqrtf(3)*a) + (j - 0.75f*a)*(j - 0.75f*a) > r*r) {
					return sqrtf((i - 0.25f*sqrtf(3)*a)*(i - 0.25f*sqrtf(3)*a) + (j - 0.75f*a)*(j - 0.75f*a)) - r;
				}
				break;
			case 3:
				if ((i + 0.25f*sqrtf(3)*a)*(i + 0.25f*sqrtf(3)*a) + (j - 0.75f*a)*(j - 0.75f*a) > r*r) {
					return sqrtf((i + 0.25f*sqrtf(3)*a)*(i + 0.25f*sqrtf(3)*a) + (j - 0.75f*a)*(j - 0.75f*a)) - r;
				}
				break;
			case 4:
				if ((i + 0.5f*sqrtf(3)*a)*(i + 0.5f*sqrtf(3)*a) + j * j > r*r) {
					return sqrtf((i + 0.5f*sqrtf(3)*a)*(i + 0.5f*sqrtf(3)*a) + j * j) - r;
				}
				break;
			case 5:
				if ((i + 0.25f*sqrtf(3)*a)*(i + 0.25f*sqrtf(3)*a) + (j + 0.75f*a)*(j + 0.75f*a) > r*r) {
					return sqrtf((i + 0.25f*sqrtf(3)*a)*(i + 0.25f*sqrtf(3)*a) + (j + 0.75f*a)*(j + 0.75f*a)) - r;
				}
				break;
			default:
				assert(false);
			}

			return -0.1f;
			break;
		case 1: // diff=1;
			r = a * SideFraction;
			switch (From[CurPath]) {
			case 0:
				if ((i - 0.5f*sqrtf(3)*a)*(i - 0.5f*sqrtf(3)*a) + (j + 0.5f*a)*(j + 0.5f*a) < r*r) {
					return r - sqrtf((i - 0.5f*sqrtf(3)*a)*(i - 0.5f*sqrtf(3)*a) + (j + 0.5f*a)*(j + 0.5f*a));
				}
				break;
			case 1:
				if ((i - 0.5f*sqrtf(3)*a)*(i - 0.5f*sqrtf(3)*a) + (j - 0.5f*a)*(j - 0.5f*a) < r*r) {
					return r - sqrtf((i - 0.5f*sqrtf(3)*a)*(i - 0.5f*sqrtf(3)*a) + (j - 0.5f*a)*(j - 0.5f*a));
				}
				break;
			case 2:
				if (i*i + (j - a)*(j - a) < r*r) {
					return r - sqrtf(i*i + (j - a)*(j - a));
				}
				break;
			case 3:
				if ((i + 0.5f*sqrtf(3)*a)*(i + 0.5f*sqrtf(3)*a) + (j - 0.5f*a)*(j - 0.5f*a) < r*r) {
					return r - sqrtf((i + 0.5f*sqrtf(3)*a)*(i + 0.5f*sqrtf(3)*a) + (j - 0.5f*a)*(j - 0.5f*a));
				}
				break;
			case 4:
				if ((i + 0.5f*sqrtf(3)*a)*(i + 0.5f*sqrtf(3)*a) + (j + 0.5f*a)*(j + 0.5f*a) < r*r) {
					return r - sqrtf((i + 0.5f*sqrtf(3)*a)*(i + 0.5f*sqrtf(3)*a) + (j + 0.5f*a)*(j + 0.5f*a));
				}
				break;
			case 5:
				if (i*i + (j + a)*(j + a) < r*r) {
					return r - sqrtf(i*i + (j + a)*(j + a));
				}
				break;
			}
			break;

		case 2: // diff=2;
			r = a * (1.0f + SideFraction);
			switch (From[CurPath]) {
			case 0:
				if ((i - sqrtf(3)*a)*(i - sqrtf(3)*a) + j * j < r*r) {
					return r - sqrtf((i - sqrtf(3)*a)*(i - sqrtf(3)*a) + j * j);
				}
				break;
			case 1:
				if ((i - 0.5f*sqrtf(3)*a)*(i - 0.5f*sqrtf(3)*a) + (j - 1.5f*a)*(j - 1.5f*a) < r*r) {
					return r - sqrtf((i - 0.5f*sqrtf(3)*a)*(i - 0.5f*sqrtf(3)*a) + (j - 1.5f*a)*(j - 1.5f*a));
				}
				break;
			case 2:
				if ((i + 0.5f*sqrtf(3)*a)*(i + 0.5f*sqrtf(3)*a) + (j - 1.5f*a)*(j - 1.5f*a) < r*r) {
					return r - sqrtf((i + 0.5f*sqrtf(3)*a)*(i + 0.5f*sqrtf(3)*a) + (j - 1.5f*a)*(j - 1.5f*a));
				}
				break;
			case 3:
				if ((i + sqrtf(3)*a)*(i + sqrtf(3)*a) + j * j < r*r) {
					return r - sqrtf((i + sqrtf(3)*a)*(i + sqrtf(3)*a) + j * j);
				}
				break;
			case 4:
				if ((i + 0.5f*sqrtf(3)*a)*(i + 0.5f*sqrtf(3)*a) + (j + 1.5f*a)*(j + 1.5f*a) < r*r) {
					return r - sqrtf((i + 0.5f*sqrtf(3)*a)*(i + 0.5f*sqrtf(3)*a) + (j + 1.5f*a)*(j + 1.5f*a));
				}
				break;
			case 5:
				if ((i - 0.5f*sqrtf(3)*a)*(i - 0.5f*sqrtf(3)*a) + (j + 1.5f*a)*(j + 1.5f*a) < r*r) {
					return r - sqrtf((i - 0.5f*sqrtf(3)*a)*(i - 0.5f*sqrtf(3)*a) + (j + 1.5f*a)*(j + 1.5f*a));
				}
				break;
			}
			break;

		case 3:  // diff=3;
			switch (From[CurPath]) {
			case 0:
				if (sqrtf(3)*i + j > a*(1.0f - 2 * SideFraction)) {
					return 0.5f*(sqrtf(3)*i + j - a * (1.0f - 2 * SideFraction));
				}
				break;
			case 1:
				if (j > a*(0.5f - SideFraction)) {
					return j - a * (0.5f - SideFraction);
				}
				break;
			case 2:
				if (-sqrtf(3)*i + j > a*(1.0f - 2 * SideFraction)) {
					return 0.5f*(-sqrtf(3)*i + j - a * (1.0f - 2 * SideFraction));
				}
				break;
			case 3:
				if (-sqrtf(3)*i - j > a*(1.0f - 2 * SideFraction)) {
					return 0.5f*(-sqrtf(3)*i - j - a * (1.0f - 2 * SideFraction));
				}
				break;
			case 4:
				if (-j > a*(0.5f - SideFraction)) {
					return -j - a * (0.5f - SideFraction);
				}
				break;
			case 5:
				if (sqrtf(3)*i - j > a*(1.0f - 2 * SideFraction)) {
					return 0.5f*(sqrtf(3)*i - j - a * (1.0f - 2 * SideFraction));
				}
				break;
			}
			break;

		case 4: // diff=4;
			r = a * (2.0f - SideFraction);
			switch (From[CurPath]) {
			case 0:
				if ((i + 0.5f*sqrtf(3)*a)*(i + 0.5f*sqrtf(3)*a) + (j + 1.5f*a)*(j + 1.5f*a) > r*r) {
					return sqrtf((i + 0.5f*sqrtf(3)*a)*(i + 0.5f*sqrtf(3)*a) + (j + 1.5f*a)*(j + 1.5f*a)) - r;
				}
				break;
			case 1:
				if ((i - 0.5f*sqrtf(3)*a)*(i - 0.5f*sqrtf(3)*a) + (j + 1.5f*a)*(j + 1.5f*a) > r*r) {
					return sqrtf((i - 0.5f*sqrtf(3)*a)*(i - 0.5f*sqrtf(3)*a) + (j + 1.5f*a)*(j + 1.5f*a)) - r;
				}
				break;
			case 2:
				if ((i - sqrtf(3)*a)*(i - sqrtf(3)*a) + j * j > r*r) {
					return sqrtf((i - sqrtf(3)*a)*(i - sqrtf(3)*a) + j * j) - r;
				}
				break;
			case 3:
				if ((i - 0.5f*sqrtf(3)*a)*(i - 0.5f*sqrtf(3)*a) + (j - 1.5f*a)*(j - 1.5f*a) > r*r) {
					return sqrtf((i - 0.5f*sqrtf(3)*a)*(i - 0.5f*sqrtf(3)*a) + (j - 1.5f*a)*(j - 1.5f*a)) - r;
				}
				break;
			case 4:
				if ((i + 0.5f*sqrtf(3)*a)*(i + 0.5f*sqrtf(3)*a) + (j - 1.5f*a)*(j - 1.5f*a) > r*r) {
					return sqrtf((i + 0.5f*sqrtf(3)*a)*(i + 0.5f*sqrtf(3)*a) + (j - 1.5f*a)*(j - 1.5f*a)) - r;
				}
				break;
			case 5:
				if ((i + sqrtf(3)*a)*(i + sqrtf(3)*a) + j * j > r*r) {
					return sqrtf((i + sqrtf(3)*a)*(i + sqrtf(3)*a) + j * j) - r;
				}
				break;
			}
			break;

		case 5: // diff=5;
			r = a * (1.0f - SideFraction);
			switch (From[CurPath]) {
			case 0:
				if (i*i + (j + a)*(j + a) > r*r) {
					return sqrtf(i*i + (j + a)*(j + a)) - r;
				}
				break;
			case 1:
				if ((i - 0.5f*sqrtf(3)*a)*(i - 0.5f*sqrtf(3)*a) + (j + 0.5f*a)*(j + 0.5f*a) > r*r) {
					return sqrtf((i - 0.5f*sqrtf(3)*a)*(i - 0.5f*sqrtf(3)*a) + (j + 0.5f*a)*(j + 0.5f*a)) - r;
				}
				break;
			case 2:
				if ((i - 0.5f*sqrtf(3)*a)*(i - 0.5f*sqrtf(3)*a) + (j - 0.5f*a)*(j - 0.5f*a) > r*r) {
					return sqrtf((i - 0.5f*sqrtf(3)*a)*(i - 0.5f*sqrtf(3)*a) + (j - 0.5f*a)*(j - 0.5f*a)) - r;
				}
				break;
			case 3:
				if (i*i + (j - a)*(j - a) > r*r) {
					return sqrtf(i*i + (j - a)*(j - a)) - r;
				}
				break;
			case 4:
				if ((i + 0.5f*sqrtf(3)*a)*(i + 0.5f*sqrtf(3)*a) + (j - 0.5f*a)*(j - 0.5f*a) > r*r) {
					return sqrtf((i + 0.5f*sqrtf(3)*a)*(i + 0.5f*sqrtf(3)*a) + (j - 0.5f*a)*(j - 0.5f*a)) - r;
				}
				break;
			case 5:
				if ((i + 0.5f*sqrtf(3)*a)*(i + 0.5f*sqrtf(3)*a) + (j + 0.5f*a)*(j + 0.5f*a) > r*r) {
					return sqrtf((i + 0.5f*sqrtf(3)*a)*(i + 0.5f*sqrtf(3)*a) + (j + 0.5f*a)*(j + 0.5f*a)) - r;
				}
				break;
			}
			break;
		}
	}

	return -0.1f;
}
Color HexGrid::TrenchColorGradient(Color Out, Color Trench, float f) const
{
	const float l1 = 0.7f;
	const float l2 = 1.4f;
	if (f < 0.0f) {
		return Trench;

	}
	if (f > l2) {
		return Out;
	}

	const float r1 = Trench.GetR();
	const float g1 = Trench.GetG();
	const float b1 = Trench.GetB();
	const float r2 = 254;
	const float g2 = 254;
	const float b2 = 254;
	const float r3 = Out.GetR();
	const float g3 = Out.GetG();
	const float b3 = Out.GetB();

	if (f < l1) {
		const float r = sqrtf((r2*r2*f + r1 * r1*(l1 - f)) / l1);
		const float g = sqrtf((g2*g2*f + g1 * g1*(l1 - f)) / l1);
		const float b = sqrtf((b2*b2*f + b1 * b1*(l1 - f)) / l1);

		return Color(int(r), int(g), int(b));
	}

	//	const float r = (r2*f + r1*(l - f)) / l;
	//	const float g = (g2*f + g1*(l - f)) / l;
	//	const float b = (b2*f + b1*(l - f)) / l;


	const float r = sqrtf((r3*r3*(f - l1) + r2 * r2*(l2 - f)) / (l2 - l1));
	const float g = sqrtf((g3*g3*(f - l1) + g2 * g2*(l2 - f)) / (l2 - l1));
	const float b = sqrtf((b3*b3*(f - l1) + b2 * b2*(l2 - f)) / (l2 - l1));

	return Color(int(r), int(g), int(b));
}


