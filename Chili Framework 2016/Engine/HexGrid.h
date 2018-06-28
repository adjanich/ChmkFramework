#pragma once
#include "RectI.h"
#include "Graphics.h"

#define PI 3.1415926535f


class HexGrid {
private:
	class Cell {
	public:
		Cell();

		void DrawBorder(Graphics& gfx, Color Trench);
		void DrawBackground(Graphics& gfx, Color Out, Color Tranch);
		void DrawHover(Graphics& gfx, Color Trench);
		void DrawSideHover(Graphics& gfx, int side, Color Out, Color Trench);

		void SwitchConnection(int Side);
		void Rot();

		void SetActive(bool in_Active);
		bool IsActive() const;
		void Initiate(const Vec2<float>& in_loc, float in_a, Color* in_Pixels, int in_PxPerCell);
	private:
		void DrawInteruptedLine(Graphics& gfx, Vec2<float> v1, Vec2<float> v2,Color Trench, Color BorderColor = Color(255, 255, 255));



	public:
		static constexpr float SideFraction = 0.3f; // part of side from both of the corners, which is solid and not covered with path;
	private:
		bool Active = true;
		bool Initiated = false;
		Vec2<float> loc = Vec2<float>(0.0f, 0.0f); // loc of center
		float a;

		bool HasConnection[6] = {false, true, true, false, true, true};

		Color* Pixels;
		int PxPerCell;
	};

public:

public:
	HexGrid(float a, int nRows, int nColumns, bool StartWithLonger = false, const RectI& rect = RectI(0, Graphics::ScreenWidth, 0, Graphics::ScreenHeight));
	HexGrid(float a, int nRows, int nColumns, bool StartWithLonger, const Vec2<float>& offset);
	~HexGrid();

	void AddOrRemoveConnection(Vec2<float> MousePos);
	void Rot(Vec2<float> MousePos);

	void Draw(Graphics& gfx, Vec2<float> MousePos);
	void DrawHover(Graphics& gfx, Vec2<float> MousePos);
	void DrawSideHover(Graphics& gfx, Vec2<float> MousePos);

	

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

	void InitiatePixels(Color Out, Color Trench);
	float InTrench(float i, float j, int nConnections, int* From, int* To) const;
	Color TrenchColorGradient(Color Out, Color Trench, float f) const;

private:
	int nRows;
	int nColumns;
	float a;
	bool StartWithLonger;
	int nCells;

	Cell* Cells;

	Color* Pixels;
	int PxPerCell;

	Vec2<float> offset = Vec2<float>(0.0f, 0.0f);

	bool Initiated = false;

};