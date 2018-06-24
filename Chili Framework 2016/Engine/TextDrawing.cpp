#include "TextDrawing.h"
#include <cassert>

Font::Font(const std::wstring& filename)

{
	Surface FontSpriteSheet = Surface(filename);

///////////////////////////////////// Tops[] and Bottoms[], nRows;
	const int width = FontSpriteSheet.GetWidth();
	const int height = FontSpriteSheet.GetHeight();

	bool LastCurMagentaRow = true;
	bool CurMagentaRow = true;
	int CurRow = 0;
	for (int j = 0; j < height; j++) {

		LastCurMagentaRow = CurMagentaRow;
		bool Continue = true;

		for (int i = 0;Continue ;i++) {
			if (i >= 100) {
				Continue = false; 
				CurMagentaRow = true;
			}
			if (FontSpriteSheet.GetPixel(i,j).GetG()>100 || FontSpriteSheet.GetPixel(i,j).GetR()<200) { 
				Continue = false; 
				CurMagentaRow = false;
			}
		}

		if (LastCurMagentaRow && !CurMagentaRow) {
			Tops[CurRow] = j;
		}
		if (!LastCurMagentaRow && CurMagentaRow) {
			Bottoms[CurRow] = j - 1;
			CurRow++;
		}
	}

	nRows = CurRow;

	////////////////////////////////////////// height of Char, verify that height is const;

	CharHeight = Bottoms[0] - Tops[0] + 1;
	for (int row = 1; row < nRows; row++) {
		assert(CharHeight == Bottoms[row] - Tops[row] + 1);
	}

	//////////////////////////////////////////  nChars, widths;

	int CurChar = 0;
	int j;

	int Left;
	int Right;

	for (int row = 0; row < nRows; row++) {
		j = (Tops[row] + Bottoms[row]) / 2;

		bool CurMagenta = true;
		bool LastCurMagenta = true;
		for (int i = 0;i < width;i++) {
			LastCurMagenta = CurMagenta;
			CurMagenta = (FontSpriteSheet.GetPixel(i, j).GetR()>200 && FontSpriteSheet.GetPixel(i, j).GetG()<100);

			if (LastCurMagenta && !CurMagenta) {
				Left = i;
			}

			if (!LastCurMagenta && CurMagenta) {
				Right = i - 1;
				CharWidths[CurChar] = Right - Left + 1;
				CurChar++;
			}
		}
	}
	nChars = CurChar;

	//////////////////////////////////////////  compute BiggestCharWidth;

	BiggestCharWidth = CharWidths[0];
	for (int CurChar = 0;CurChar < nChars;CurChar++) {
		if (BiggestCharWidth<CharWidths[CurChar]) {
			BiggestCharWidth = CharWidths[CurChar];
		}
	}



	//////////////////////////////////////////  allocate bool array, ;

	Data = new bool[nChars*BiggestCharWidth*CharHeight];

	CurChar = 0;

	for (int row = 0; row < nRows; row++) {
		j = (Tops[row] + Bottoms[row]) / 2;

		bool CurMagenta = true;
		bool LastCurMagenta = true;
		for (int i = 0;i < width;i++) {
			LastCurMagenta = CurMagenta;
			CurMagenta = (FontSpriteSheet.GetPixel(i, j).GetR()>200 && FontSpriteSheet.GetPixel(i, j).GetG()<100);

			if (LastCurMagenta && !CurMagenta) {
				Left = i;
			}

			if (!LastCurMagenta && CurMagenta) {
				Right = i - 1;

				for (int x = Left; x <= Right;x++) {
					for (int y = Tops[row];y <= Bottoms[row];y++) {
						Data[(CurChar*CharHeight+(y-Tops[row]))*BiggestCharWidth+(x-Left)] = (FontSpriteSheet.GetPixel(x, y).GetB() > 150);
					}
				}
				CurChar++;
			}
		}
	}


	SpaceWidth = CharWidths[0];
}

Font::~Font() {
	delete[] Data;
	Data = nullptr;

	
}

////////////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
///////////////////////////////////////////////////////==\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//////////////////////////////////////////////////////=/\=\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////////////////////=/##\=\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\=\##/=///////////////////////////////////////////////////////////////////
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\=\/=///////////////////////////////////////////////////////////////////
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\==///////////////////////////////////////////////////////////////////
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\///////////////////////////////////////////////////////////////////


Text::Text(const std::wstring & in_txt, const Font& fnt, const Color & c)
	:
	Text(std::string(in_txt.begin(),in_txt.end()),fnt)
{
}

Text::Text(const std::wstring & in_txt, const Font& fnt, int width, const Color & c)
	:
	Text(std::string(in_txt.begin(), in_txt.end()), fnt, width)
{
}

Text::Text(const std::string & in_txt, const Font & fnt, const Color & c)
	:
	c(c)
{
	std::string txt;
////////////////////////////////////////////////// allow only printable chars;
#ifndef NDEBUG
	if (SupportedChars(in_txt)) {
		txt = in_txt;
	}
	else {
		throw std::runtime_error("TEXT ERR\nNot supported chars in text:\n\"" + in_txt + "\"");
	}
#else
	txt = "";
	for (auto it = in_txt.begin(); it != in_txt.end(); ++it) {
		if (*it == 10 || (*it >= 32 && *it <= 126)) {
			txt += *it;
		}
	}


#endif

///////////////////////////////////////////////////////determine nRows, height;

	nRows = 1;
	for (auto it = txt.begin(); it != txt.end(); ++it) {
		if (*it == 10) {
			nRows++;
		}
	}

	height = nRows*fnt.CharHeight + (nRows - 1)*fnt.RowSpaceHeight;

////////////////////////////////////////// new strings for rows
	std::string* rows = new std::string[nRows];

	int CurRow = 0;
	for (auto it = txt.begin(); it != txt.end(); ++it) {
		if (*it == 10) {
			CurRow++;
		}
		else {
			rows[CurRow] += *it;
		}
	}

////////////////////////////////////////////  widths of rows, max of widths -> width;

	int CurRowWidth;
	width = 0;
	for (int CurRow = 0; CurRow < nRows;CurRow++) {
		CurRowWidth = 0;
		for (auto it = rows[CurRow].begin(); it != rows[CurRow].end(); ++it) {
			if (*it==32) {
				CurRowWidth += fnt.SpaceWidth;
			}
			else {
				CurRowWidth += fnt.CharWidths[*it - fnt.FirstCharAsciiCode];
			}
		}
		if (CurRowWidth > width) {
			width = CurRowWidth;
		}
	}

	////////////////////////////////////////////  allocate Surface, put data there;

	srf = new Surface(width, height,Color(),Color());
	srfExist = true;

	int x = 0; // position of current char in the surface coordinate system in pixels;
	int y = 0; // position of current char in the surface coordinate system in pixels;

	for (auto it = txt.begin(); it != txt.end(); ++it) {
		if (*it == 10) {
			y += (fnt.CharHeight + fnt.RowSpaceHeight);
			x = 0;
		}
		else if (*it == 32) {
			x += fnt.SpaceWidth;
		}
		else {
			for (int i = 0; i < fnt.CharWidths[*it - fnt.FirstCharAsciiCode]; i++) {
				for (int j = 0; j < fnt.CharHeight; j++) {
					if (fnt.Data[((*it - fnt.FirstCharAsciiCode)*fnt.CharHeight + (j))*fnt.BiggestCharWidth + (i)]) {
						srf->PutPixel(x + i, y + j, c);
					}
				}
			}
			x += fnt.CharWidths[*it - fnt.FirstCharAsciiCode];
		}
	}

	//////////////////////////////////////////////////////////// clean the mess in the RAM;

	delete[] rows;

}

Text::Text(const std::string & in_txt, const Font & fnt, int in_width, const Color& c)
	:
	c(c),
	width(in_width)
{
	std::string txt;
	////////////////////////////////////////////////// allow only printable chars;
#ifndef NDEBUG
	if (SupportedChars(in_txt)) {
		txt = in_txt;
	}
	else {
		throw std::runtime_error("TEXT ERR\nNot supported chars in text:\n\"" + in_txt + "\"");
	}
#else
	txt = "";
	for (auto it = in_txt.begin(); it != in_txt.end(); ++it) {
		if (*it == 10 || (*it >= 32 && *it <= 126)) {
			txt += *it;
		}
	}
#endif

	////////////////////////////////////////////////// don't let the width be too low;
#ifndef NDEBUG
	if (width < fnt.BiggestCharWidth) {
		throw std::runtime_error("TEXT ERR\nSpecified width is less than BiggistCharWidth in text:\n\"" + in_txt + "\"");
	}
#else
	if (width < fnt.BiggestCharWidth) {
		width = fnt.BiggestCharWidth;
	}
#endif




	//////////////////////////////////////////////////// nWords;

	int nWords = 1;
	for (auto it = txt.begin(); it != txt.end(); ++it) {
		if (*it == 10 || *it == 32) {
			nWords++;
		}
	}

	/////////////////////////////////////////////////////////// new strings for words+WordLenghts;
	std::string* words = new std::string[nWords];

	int* WordLenghts = new int[nWords];
	for (int i = 0; i < nWords; i++) {
		WordLenghts[i] = 0;
	}

	int CurWord = 0;
	for (auto it = txt.begin(); it != txt.end(); ++it) {
		if (*it == 10 || *it == 32) {
			CurWord++;
		}
		else {
			words[CurWord] += *it;
			WordLenghts[CurWord] += fnt.CharWidths[*it - fnt.FirstCharAsciiCode];
		}
	}

	////////////////////////////////////////////   nRows, width;

	int CurRow = 0;
	int x = 0;
	bool FirstWordInRow = true;
	for (CurWord = 0; CurWord < nWords; CurWord++) {
		if (!FirstWordInRow) {
			if (x + fnt.SpaceWidth + WordLenghts[CurWord] > width) { // do Enter
				CurRow++;
				x = 0;
				FirstWordInRow = true;
			}
			else { // insert the word
				x += (fnt.SpaceWidth + WordLenghts[CurWord]);
				FirstWordInRow = false;
			}
		}

		if (FirstWordInRow) {	//////////////////// parse through chars;
			for (auto it = words[CurWord].begin(); it != words[CurWord].end(); ++it) {
				if (x + fnt.CharWidths[*it - fnt.FirstCharAsciiCode] > width) { // do Enter			
					CurRow++;
					x = 0;
				}
				x += fnt.CharWidths[*it - fnt.FirstCharAsciiCode];
			}
			FirstWordInRow = false;
		}
	}

	nRows = CurRow + 1;
	height = nRows * fnt.CharHeight + (nRows - 1)*fnt.RowSpaceHeight;

	////////////////////////////////////////////  allocate Surface, put data there;

	srf = new Surface(width, height, Color(), Color());
	srfExist = true;

	CurRow = 0;
	x = 0;
	int y = 0;
	FirstWordInRow = true;
	for (CurWord = 0; CurWord < nWords; CurWord++) {
		if (!FirstWordInRow) {
			if (x + fnt.SpaceWidth + WordLenghts[CurWord] > width) { // do Enter
				CurRow++;
				y += (fnt.CharHeight+fnt.RowSpaceHeight);
				x = 0;
				FirstWordInRow = true;
			}
			else { // insert the word
				x += fnt.SpaceWidth;
				for (auto it = words[CurWord].begin(); it != words[CurWord].end(); ++it) {
					//copy letter
					for (int i = 0; i < fnt.CharWidths[*it - fnt.FirstCharAsciiCode]; i++) {
						for (int j = 0; j < fnt.CharHeight; j++) {
							if (fnt.Data[((*it - fnt.FirstCharAsciiCode)*fnt.CharHeight + (j))*fnt.BiggestCharWidth + (i)]) {
								srf->PutPixel(x + i, y + j, c);
							}
						}
					}
					x += fnt.CharWidths[*it - fnt.FirstCharAsciiCode];
				}
				FirstWordInRow = false;
			}
		}

		if (FirstWordInRow) {	//////////////////// parse through chars;
			for (auto it = words[CurWord].begin(); it != words[CurWord].end(); ++it) {
				if (x + fnt.CharWidths[*it - fnt.FirstCharAsciiCode] > width) { // do Enter			
					CurRow++;
					y += (fnt.CharHeight + fnt.RowSpaceHeight);
					x = 0;
				}
				//copy letter
				for (int i = 0; i < fnt.CharWidths[*it - fnt.FirstCharAsciiCode]; i++) {
					for (int j = 0; j < fnt.CharHeight; j++) {
						if (fnt.Data[((*it - fnt.FirstCharAsciiCode)*fnt.CharHeight + (j))*fnt.BiggestCharWidth + (i)]) {
							srf->PutPixel(x + i, y + j, c);
						}
					}
				}
				x += fnt.CharWidths[*it - fnt.FirstCharAsciiCode];
			}
			FirstWordInRow = false;
		}
	}

	//////////////////////////////////////////////////////////// clean the mess in the RAM;

	delete[] words;
	delete[] WordLenghts;

}

Text::Text(const std::wstring & in_txt, const Font & fnt)
	:
	Text(in_txt,fnt,Color(255,255,255))
{
}

Text::Text(const std::wstring & in_txt, const Font & fnt, int width)
	:
	Text(in_txt, fnt, width, Color(255, 255, 255))
{
}

Text::Text(const std::string & in_txt, const Font & fnt)
	:
	Text(in_txt, fnt, Color(255, 255, 255))
{
}

Text::Text(const std::string & in_txt, const Font & fnt, int width)
	:
	Text(in_txt, fnt, width, Color(255, 255, 255))

{
}

Text::Text(const Text & rhs)
{
	srfExist = rhs.srfExist;
	if (srfExist) {
		height = rhs.height;
		width = rhs.width;
		srf = new Surface(*rhs.srf);
		nRows = rhs.nRows;
		c = rhs.c;
	}

}

Text & Text::operator=(const Text & rhs)
{
	if (srfExist && rhs.srfExist) {
		*srf = *rhs.srf;
		height = rhs.height;
		width = rhs.width;
		nRows = rhs.nRows;
		c = rhs.c;
	}
	if (!srfExist && rhs.srfExist) {
		height = rhs.height;
		width = rhs.width;
		srf = new Surface(*rhs.srf);
		nRows = rhs.nRows;
		c = rhs.c;
	}
	if (srfExist && !rhs.srfExist) {
		delete srf;
		srf = nullptr;
	}
	if (!srfExist && !rhs.srfExist) {
	}
	srfExist = rhs.srfExist;
	return *this;
}

Text::~Text()
{
	if (srfExist) {
		delete srf;
		srf = nullptr;
	}
}



void Text::DeleteData()
{
	if (srfExist) {
		delete srf;
		srf = nullptr;
		srfExist = false;
	}

}

int Text::GetWidth() const
{
#ifndef NDEBUG
	if (srfExist) {
		return width;
	}
	throw std::exception("TEXT ERR\nSome BULLSHIT is trying to get WIDTH from deleted or not initialized Text object.");
#else
	if (srfExist) {
		return width;
	}
	return 0;
#endif
}

int Text::GetHeight() const
{

#ifndef NDEBUG
	if (srfExist) {
		return height;
	}
	throw std::exception("TEXT ERR\nSome BULLSHIT is trying to get HEIGHT from deleted or not initialized Text object.");
#else
	if (srfExist) {
		return height;
	}
	return 0;
#endif
}

const Surface& Text::GetSurface()
{
	//assert(srfExist);
#ifndef NDEBUG
	if (!srfExist) {
		throw std::exception("TEXT ERR\nSome BULLSHIT is trying to get Surface& from deleted or not initialized Text object.");
	}
#else
	// not 100% sure so far, whether something here ????	????	????	????	????	????	????	????
#endif
	return *srf;
}

std::string  Text::ToSrtring(int x)
{

	if (x == 0) { 
		return "0";
	}
		
	std::string str;

	bool Negative = (x < 0);
	x = abs(x);

	do {
		str = char(char(x%10)+'0') + str;
		x /= 10;
	} while (x>0);

	if (Negative) {
		str = '-' + str;
	}

	return str;
}

std::string Text::ToSrtring(double x, int nCif)
{
	std::string str;

	bool Negative = (x < 0);
	x = abs(x);

	int cifBeforeDot = int(log10(x));
	if (cifBeforeDot <= 0) {
		str = "0.";
	}
	else {
		str = "neco.";
	}

	double pwr10 = 1.0;
	for (int CurCif = 1; CurCif <= nCif; CurCif++){
		pwr10 *= 0.1;
		int CifVal = 0;
		while (x > pwr10) {
			CifVal++;
			x -= pwr10;
		}
		str += CifVal + '0';
	}

	if (Negative) {
		str = '-' + str;
	}



	return str;

}

bool Text::SupportedChars(const std::wstring & txt) const
{
	return SupportedChars(std::string(txt.begin(),txt.end()));
}

bool Text::SupportedChars(const std::string & txt) const
{
	for (auto it = txt.begin(); it != txt.end(); ++it) {
		if (!(*it == 10 || (*it >= 32 && *it <= 126))) {
			return false;
		}
	}
	return true;
}
