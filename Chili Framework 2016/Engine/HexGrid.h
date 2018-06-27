#pragma once
#include "RectI.h"
#include "Graphics.h"

#define PI 3.1415926535f


class HexGrid {
private:
	class Cell {
	public:
		Cell();

		void Draw(Graphics& gfx);
		void DrawSpecial(Graphics& gfx);

		void SetActive(bool in_Active);
		bool IsActive() const;
		void SetLoc(const Vec2<float>& in_loc, float in_a);
	private:
		bool Active = true;
		bool Initiated = false;
		Vec2<float> loc = Vec2<float>(0.0f, 0.0f); // loc of center
		float a;
	};

public:

public:
	HexGrid(float a, int nRows, int nColumns, bool StartWithLonger = false, const RectI& rect = RectI(0, Graphics::ScreenWidth, 0, Graphics::ScreenHeight));
	HexGrid(float a, int nRows, int nColumns, bool StartWithLonger, const Vec2<float>& offset);
	~HexGrid();

	void Draw(Graphics& gfx, Vec2<float> MousePos);

private:
	float GetWidth() const;
	float GetHeight() const;
	float GetWidth(float a, int nColumns) const;
	float GetHeight(float a, int nRows) const;

	int nCellsInRow(int Row) const;

	int CelliFromVec(Vec2<float> vec) const;
	int CelliFromRC(int Row, int Column) const;
	int RowFromCelli(int Celli) const;
	int ColumnFromCelli(int Celli) const;
	Vec2<float> VecCenter(int Celli) const;
	Vec2<float> VecCenter(int Row, int Column) const;
	Vec2<float> VecCorner(int Celli, int Corneri) const;
	Vec2<float> VecCorner(int Row, int Column, int Corneri)const;
	int SectorFromVec(Vec2<float> vec) const;
	int AdjacentCelli(int Celli, int Dir);

private:
	int nRows;
	int nColumns;
	float a;
	bool StartWithLonger;
	int nCells;

	Cell* Cells;

	Vec2<float> offset = Vec2<float>(0.0f, 0.0f);

	bool Initiated = false;

};