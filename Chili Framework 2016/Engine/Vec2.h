#pragma once

template <typename T>
struct Vec2 {
	Vec2(T x, T y)
		:
		x(x),
		y(y)
	{
	}
	Vec2(const Vec2& rhs) :
		x(rhs.x),
		y(rhs.y)
	{
	}
	Vec2& operator=(const Vec2& rhs) {
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	Vec2 operator+(const Vec2& rhs) const {
		return Vec2(x + rhs.x, y + rhs.y);
	}
	Vec2& operator+=(const Vec2& rhs) {
		return *this = *this + rhs;
	}

	Vec2 operator-(const Vec2& rhs) const {
		return Vec2(x - rhs.x, y - rhs.y);
	}
	Vec2& operator-=(const Vec2& rhs)
	{
		return *this = *this - rhs;
	}

	Vec2 operator*(int rhs) const
	{
		return Vec2(x*rhs, y*rhs);
	}
	Vec2& operator*=(int rhs) {
		return *this = *this * rhs;
	}

	Vec2 operator/(int rhs) const
	{
		return Vec2(x / rhs, y / rhs);
	}
	Vec2& operator/=(int rhs) {
		return *this = *this / rhs;
	}

	T Dot(const Vec2& rhs) const {
		return x*rhs.x + y*rhs.y;
	}
	T Cross(const Vec2& rhs) const {
		return x*rhs.y - y*rhs.x;
	}


	T x;
	T y;

};




