#pragma once

#include "Surface.h"
#include "RectI.h"
#include <string>

class Font {
	friend class Text;
public:
	Font(const std::wstring& filename);
	~Font();

private:

	static constexpr int MaxnRows = 10;
	int nRows;
	int Tops[MaxnRows];
	int Bottoms[MaxnRows];

	static constexpr int MaxnChars = 100;
	int nChars;
	int CharHeight;
	int CharWidths[MaxnChars];
	int BiggestCharWidth;

	bool* Data;

	const char FirstCharAsciiCode = 32;
	int SpaceWidth;
	int RowSpaceHeight = -10;

};

class Text {
public:
	Text(const std::wstring& in_txt, const Font& fnt);
	Text(const std::wstring& in_txt, const Font& fnt, int width);
	Text(const std::string& in_txt, const Font& fnt);
	Text(const std::string& in_txt, const Font& fnt, int width);
	Text(const std::wstring& in_txt, const Font& fnt, const Color& c);
	Text(const std::wstring& in_txt, const Font& fnt, int width, const Color& c);
	Text(const std::string& in_txt, const Font& fnt, const Color& c);
	Text(const std::string& in_txt, const Font& fnt, int width, const Color& c);
	Text(const Text& rhs);
	Text& operator=(const Text& rhs);
	~Text();
	
	void DeleteData();

	int GetWidth() const;
	int GetHeight() const;

	const Surface& GetSurface();

	static std::string ToSrtring(int x);

private:
	bool SupportedChars(const std::wstring& txt) const;
	bool SupportedChars(const std::string& txt) const;

	Surface* srf = nullptr;
	bool srfExist;

	int height;
	int width;

	int nRows;

	Color c;




};