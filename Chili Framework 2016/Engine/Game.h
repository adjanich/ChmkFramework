
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <random>
#include "Surface.h"
#include "RectI.h"
#include "TextDrawing.h"
#include "HexGrid.h"



class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();

private:
	MainWindow& wnd;
	Graphics gfx;

	std::mt19937 rng;

	HexGrid hxg;

	bool M = false;
	bool pM = false;
	bool Space = false;
	bool pSpace = false;

	int State = 0;

	//Font fnt = Font(L"testfont.bmp");
};