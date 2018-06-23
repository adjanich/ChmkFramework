
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <random>

#define PI 3.141592653589793238462643383279502884197



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

	int pwr(int x, int y);
	int pwr(int y);

private:
	MainWindow& wnd;
	Graphics gfx;

	std::mt19937 rng;

	int lvl = 13;
	double initX = 400.0;
	double initY = 400.0;
	double initDir = PI;
	double dirStep = 0.1*PI;
	double initStep = 100.0;
	double stepCoef = 0.7;
	int ClrShift = 0;



	
};