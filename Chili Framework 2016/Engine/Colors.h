
#pragma once

class Color
{
public:
	unsigned int dword;
public:
	constexpr Color() : dword() {}
	constexpr Color( const Color& col )
		:
		dword( col.dword )
	{}
	constexpr Color( unsigned int dw )
		:
		dword( dw )
	{}
	constexpr Color( unsigned char x,unsigned char r,unsigned char g,unsigned char b )
		:
		dword( (x << 24u) | (r << 16u) | (g << 8u) | b )
	{}
	constexpr Color( unsigned char r,unsigned char g,unsigned char b )
		:
		dword( (r << 16u) | (g << 8u) | b )
	{}
	constexpr Color( Color col,unsigned char x )
		:
		Color( (x << 24u) | col.dword )
	{}
	Color& operator =( Color color )
	{
		dword = color.dword;
		return *this;
	}
	constexpr unsigned char GetX() const
	{
		return dword >> 24u;
	}
	constexpr unsigned char GetA() const
	{
		return GetX();
	}
	constexpr unsigned char GetR() const
	{
		return (dword >> 16u) & 0xFFu;
	}
	constexpr unsigned char GetG() const
	{
		return (dword >> 8u) & 0xFFu;
	}
	constexpr unsigned char GetB() const
	{
		return dword & 0xFFu;
	}
	void SetX( unsigned char x )
	{
		dword = (dword & 0xFFFFFFu) | (x << 24u);
	}
	void SetA( unsigned char a )
	{
		SetX( a );
	}
	void SetR( unsigned char r )
	{
		dword = (dword & 0xFF00FFFFu) | (r << 16u);
	}
	void SetG( unsigned char g )
	{
		dword = (dword & 0xFFFF00FFu) | (g << 8u);
	}
	void SetB( unsigned char b )
	{
		dword = (dword & 0xFFFFFF00u) | b;
	}
	
	static Color& Hue(double h) {
		int x = (int(h * 6 * 255) % (6 * 255));

		int r=255;
		int g=255;
		int b=255;

		if (x >= 0 * 255 && x <= 1 * 255) {
			r = 0;
			g = 255;
			b = x;
		}
		if (x >= 1 * 255 && x <= 2 * 255) {
			r = 0;
			g = 2 * 255 - x;
			b = 255;
		}
		if (x >= 2 * 255 && x <= 3 * 255) {
			r = -2*255 + x;
			g = 0;
			b = 255;
		}
		if (x >= 3 * 255 && x <= 4 * 255) {
			r = 255;
			g = 0;
			b = 4*255-x;
		}
		if (x >= 4 * 255 && x <= 5 * 255) {
			r = 255;
			g = -4*255+x;
			b = 0;
		}
		if (x >= 5 * 255 && x <= 6 * 255) {
			r = 6*255-x;
			g = 255;
			b = 0;
		}

		return Color(r, g, b);
	}
	static Color& Hue(int x, int y) {
		return Hue(double(x)/double(y));
	}

};

namespace Colors
{
	static constexpr Color MakeRGB( unsigned char r,unsigned char g,unsigned char b )
	{
		return (r << 16) | (g << 8) | b;
	}
	static constexpr Color White = MakeRGB( 255u,255u,255u );
	static constexpr Color Black = MakeRGB( 0u,0u,0u );
	static constexpr Color Gray = MakeRGB( 0x80u,0x80u,0x80u );
	static constexpr Color LightGray = MakeRGB( 0xD3u,0xD3u,0xD3u );
	static constexpr Color Red = MakeRGB( 255u,0u,0u );
	static constexpr Color Green = MakeRGB( 0u,255u,0u );
	static constexpr Color Blue = MakeRGB( 0u,0u,255u );
	static constexpr Color Yellow = MakeRGB( 255u,255u,0u );
	static constexpr Color Cyan = MakeRGB( 0u,255u,255u );
	static constexpr Color Magenta = MakeRGB( 255u,0u,255u );
}