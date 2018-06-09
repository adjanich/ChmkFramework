#pragma once

#include "Vec2.h"

class RectI {
public:
	RectI(int x1, int x2, int y1, int y2);
	RectI(const Vec2<int>& v1, const Vec2<int>& v2);
	RectI(const RectI& rhs);
	RectI& operator=(const RectI& rhs);

	int Left() const;
	int Right() const;
	int Top() const;
	int Bottom() const;

	Vec2<int> TopLeft() const;
	Vec2<int> TopRight() const;
	Vec2<int> BottomLeft() const;
	Vec2<int> BottomRight() const;
	Vec2<int> Center() const;

	int width();
	int height();

	RectI operator+(const Vec2<int>& rhs);
	RectI& operator+=(const Vec2<int>& rhs);

	RectI operator-(const Vec2<int>& rhs);
	RectI& operator-=(const Vec2<int>& rhs);

	bool Overlapping(const RectI& rhs)const;
	bool Containing(const RectI& rhs)const;
	bool ContainedIn(const RectI& rhs)const;

private:
	int x1;
	int x2;
	int y1;
	int y2;

};