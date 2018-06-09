
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <random>
#include "Surface.h"
#include "RectI.h"
#include "TextDrawing.h"



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

	Surface srf = Surface(L"ale.bmp");

	Font fnt = Font(L"testfont.bmp");



	
};