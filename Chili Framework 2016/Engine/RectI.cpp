#include "RectI.h"

RectI::RectI(int x1, int x2, int y1, int y2)
	:
	x1(x1),
	x2(x2),
	y1(y1),
	y2(y2)
{
}

RectI::RectI(const Vec2<int>& v1, const Vec2<int>& v2)
	:
	x1(v1.x),
	x2(v2.x),
	y1(v1.y),
	y2(v2.y)
{
}

RectI::RectI(const RectI &rhs)
	:
	x1(rhs.x1),
	x2(rhs.x2),
	y1(rhs.y1),
	y2(rhs.y2)
{
}

RectI & RectI::operator=(const RectI & rhs)
{
		x1=rhs.x1;
		x2=rhs.x2;
		y1=rhs.y1;
		y2=rhs.y2;

		return *this;

}

int RectI::Left() const
{
	return x1;
}

int RectI::Right() const
{
	return x2;
}

int RectI::Top() const
{
	return y1;
}

int RectI::Bottom() const
{
	return y2;
}

Vec2<int> RectI::TopLeft() const
{
	return Vec2<int>(Left(), Top());
}

Vec2<int> RectI::TopRight() const
{
	return Vec2<int>( Right(), Top());
}

Vec2<int> RectI::BottomLeft() const
{
	return Vec2<int>(Left(), Bottom());
}

Vec2<int> RectI::BottomRight() const
{
	return Vec2<int>(Right(), Bottom());
}

Vec2<int> RectI::Center() const
{
	return Vec2<int>((Right()+Left())/2, (Bottom()+Top())/2);
}

int RectI::width()
{
	return x2-x1;
}

int RectI::height()
{
	return y2-y1;
}

RectI  RectI::operator+(const Vec2<int>& rhs)
{
	return RectI(x1 + rhs.x, x2 + rhs.x, y1 + rhs.y, y2 + rhs.y);
}

RectI & RectI::operator+=(const Vec2<int>& rhs)
{
	return *this = *this + rhs;
}

RectI  RectI::operator-(const Vec2<int>& rhs)
{
	return RectI(x1 - rhs.x, x2 - rhs.x, y1 - rhs.y, y2 - rhs.y);
}

RectI & RectI::operator-=(const Vec2<int>& rhs)
{
	return *this = *this - rhs;
}

bool RectI::Overlapping(const RectI & rhs) const
{
	return x1<rhs.x2 && x2>rhs.x1 && y1<rhs.y2 && y2>rhs.y1;
}

bool RectI::Containing(const RectI & rhs) const
{
	return x1<=rhs.x1 && x2>=rhs.x2 && y1<=rhs.y1 && y2>=rhs.y2;
}

bool RectI::ContainedIn(const RectI & rhs) const
{
	return x1>=rhs.x1 && x2<=rhs.x2 && y1>=rhs.y1 && y2<=rhs.y2;
}
