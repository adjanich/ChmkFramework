#pragma once

#include "Colors.h"
#include <string>

class Surface {
public:
	Surface(const std::wstring& filename);
	Surface(const std::wstring& filename, Color c1, Color c2);
	Surface(int width, int height, Color c1, Color c2);
	Surface(int width, int height);
	Surface(const Surface& rhs);
	~Surface();
	Surface& operator=(const Surface& rhs);
	

	void PutPixel(int x, int y, Color c);
	Color& GetPixel(int x, int y) const;
	int GetWidth() const;
	int GetHeight() const;

	bool ShouldBeDrawn(int i, int j) const;

private:
	int width;
	int height;

	int r1;
	int r2;
	int g1;
	int g2;
	int b1;
	int b2;

	bool GreenScreen = false;

	Color* pPixels = nullptr;

};