
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <random>

#ifndef NDEBUG
#include "TextDrawing.h"
#endif

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

	void DrawRect(int x1, int x2, int y1, int y2);

#ifndef NDEBUG
	Font fnt = Font(L"testfont.bmp");
	Surface srf = Surface(1, 1);
#endif

private:
	MainWindow& wnd;
	Graphics gfx;

	std::mt19937 rng;

	int lvl = 12;
	double initX = 400.0;
	double initY = 400.0;
	double initDir = PI;
	double dirStep1 = 0.1*PI;
	double dirStep2 = -0.1*PI;
	double initStep = 100.0;
	double stepCoef = 0.7;

	const double leftStepCoefMax = 1.05;
	const double leftStepCoefMin = 0.8;
	double leftStepCoef = leftStepCoefMax;
	double leftStepCoefCurP = 0.0;
	const double leftStepCoefP1 = 2 * PI;//for cos
	const double leftStepCoefP2 = 16.0;//for const

	int ClrShift = 0;

	bool stepCoefUp = true;

	double x1;
	double x2;
	double y1;
	double y2;
	double vx = 1.0;
	double vy = 1.0;
	const double a = 0.05;
	const double aROT = 0.01;
	const double vMax = 5.0;
	const double friction = 0.99;

	const double g = 0.005;

	const double margin = 10.0;
	const double marginROT = 50.0;

};