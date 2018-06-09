#include "Surface.h"
#include <cassert>
#include "ChiliWin.h"
#include <fstream>

Surface::Surface(const std::wstring & filename)
{
	std::ifstream file(filename,std::ios::binary);
	if (!file) { 
		throw std::runtime_error("SURFICE ERR:\nCouldnt load file:\n "+std::string(filename.begin(),filename.end())); 
	}

	BITMAPFILEHEADER bmFileHeader;
	file.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader));

	BITMAPINFOHEADER bmInfoHeader;
	file.read(reinterpret_cast<char*>(&bmInfoHeader),sizeof(bmInfoHeader));


	if (bmInfoHeader.biBitCount != 24 && bmInfoHeader.biBitCount != 32) {
		throw std::runtime_error("SURFICE ERR:\nBitCount is neither 32 nor 24 in file:\n " + std::string(filename.begin(), filename.end()));
	}
	if (bmInfoHeader.biCompression != BI_RGB) {
		throw std::runtime_error("SURFICE ERR:\nCompression not supported. Err in file:\n " + std::string(filename.begin(), filename.end()));
	}


	width = bmInfoHeader.biWidth;
	height = bmInfoHeader.biHeight;

	const bool flipped = (height > 0);
	height = abs(height);
	const bool Is32b = (bmInfoHeader.biBitCount == 32);

	const int padding = width % 4;

	pPixels = new Color[width*height];

	file.seekg(bmFileHeader.bfOffBits);

	if (flipped) {
		for (int j = height-1; j >= 0; j--) {
			for (int i = 0; i < width; i++) {
				pPixels[j*width + i] = Color(file.get(), file.get(), file.get());
				if (Is32b) { file.seekg(1, std::ios::cur); }
			}
			if (!Is32b) {
				file.seekg(padding, std::ios::cur);
			}
		}
	}
	else {
		for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {
				pPixels[j*width + i] = Color(file.get(), file.get(), file.get());
				if (Is32b) { file.seekg(1, std::ios::cur); }
			}
			if (!Is32b) {
				file.seekg(padding, std::ios::cur);
			}
		}
	}

}

Surface::Surface(const std::wstring & filename, Color c1, Color c2)
	:
	Surface(filename)
{
	if (c1.GetR() < c2.GetR()) {
		r1 = c1.GetR();
		r2 = c2.GetR();
	}
	else {
		r1 = c2.GetR();
		r2 = c1.GetR();
	}
	if (c1.GetG() < c2.GetG()) {
		g1 = c1.GetG();
		g2 = c2.GetG();
	}
	else {
		g1 = c2.GetG();
		g2 = c1.GetG();
	}
	if (c1.GetB() < c2.GetB()) {
		b1 = c1.GetB();
		b2 = c2.GetB();
	}
	else {
		b1 = c2.GetB();
		b2 = c1.GetB();
	}
	GreenScreen = true;


}

Surface::Surface(int width, int height, Color c1, Color c2)
	:
	width(width),
	height(height)
{
	pPixels = new Color[width*height];

	if (c1.GetR() < c2.GetR()) {
		r1 = c1.GetR();
		r2 = c2.GetR();
	}
	else {
		r1 = c2.GetR();
		r2 = c1.GetR();
	}
	if (c1.GetG() < c2.GetG()) {
		g1 = c1.GetG();
		g2 = c2.GetG();
	}
	else {
		g1 = c2.GetG();
		g2 = c1.GetG();
	}
	if (c1.GetB() < c2.GetB()) {
		b1 = c1.GetB();
		b2 = c2.GetB();
	}
	else {
		b1 = c2.GetB();
		b2 = c1.GetB();
	}
	GreenScreen = true;
}

Surface::Surface(int width, int height)
	:
	width(width),
	height(height)
{
	pPixels = new Color[width*height];
}

Surface::Surface(const Surface & rhs)
{
	width = rhs.width;
	height = rhs.height;
	pPixels = new Color[width*height];
	for (int i = 0;i < width*height;i++) {
		pPixels[i] = rhs.pPixels[i];
	}

	r1 = rhs.r1;
	r2 = rhs.r2;
	g1 = rhs.g1;
	g2 = rhs.g2;
	b1 = rhs.b1;
	b2 = rhs.b2;

	GreenScreen = rhs.GreenScreen;
}

Surface::~Surface()
{
	delete[] pPixels;
	pPixels = nullptr;
}

Surface & Surface::operator=(const Surface & rhs)
{
	delete[] pPixels;

	width = rhs.width;
	height = rhs.height;
	pPixels = new Color[width*height];
	for (int i = 0;i < width*height;i++) {
		pPixels[i] = rhs.pPixels[i];
	}

	r1 = rhs.r1;
	r2 = rhs.r2;
	g1 = rhs.g1;
	g2 = rhs.g2;
	b1 = rhs.b1;
	b2 = rhs.b2;

	GreenScreen = rhs.GreenScreen;


	return *this;
}

void Surface::PutPixel(int x, int y, Color c)
{
	assert(x>=0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	pPixels[y*width + x] = c;
}

Color & Surface::GetPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	return pPixels[y*width + x];
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}

bool Surface::ShouldBeDrawn(int i, int j) const
{
	if (GreenScreen == false) { return true; }
	if (GetPixel(i, j).GetR() < r1 || GetPixel(i, j).GetR() > r2) { return true; }
	if (GetPixel(i, j).GetG() < g1 || GetPixel(i, j).GetG() > g2) { return true; }
	if (GetPixel(i, j).GetB() < b1 || GetPixel(i, j).GetB() > b2) { return true; }
	return false;


}
