
#include "MainWindow.h"
#include "Game.h"
#include <string>



Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	rng(std::random_device()())
{
	std::uniform_real_distribution<double> Dist(0, 2 * PI);
	dirStep2 = Dist(rng);
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{

}

void Game::ComposeFrame()
{


	leftStepCoefCurP += 0.01;
	if (leftStepCoefCurP > leftStepCoefP1 + leftStepCoefP2) { leftStepCoefCurP = 0; }
	if (leftStepCoefCurP < leftStepCoefP1) {
		leftStepCoef = 0.5*(leftStepCoefMax + leftStepCoefMin) + 0.5*(leftStepCoefMax - leftStepCoefMin)*cos(leftStepCoefCurP);
	}
	else { 
		leftStepCoef = leftStepCoefMax; 
	}



	int imax = pwr(lvl);

	for (int i = 0; i < imax; i++) {
		int temp = i;
		double x = initX;
		double y = initY;
		double dir = initDir;
		double step = initStep;
		int pwr2 = imax;
		for (int digitOrder = 0; digitOrder < lvl; digitOrder++) {
			pwr2 /= 2;
			bool digitVal = (temp >= pwr2);
			temp %= pwr2;

			if (digitVal) { dir += dirStep1; }
			else { dir += dirStep2; }
			x += (step * sin(dir));
			y += (step * cos(dir));

			step *= stepCoef;
			if (digitVal) { step *= leftStepCoef; }

		}
		if (x + 1 >= 0 && x + 1 < gfx.ScreenWidth && y >= 0 && y < gfx.ScreenHeight) { gfx.PutPixel(x + 1, y, Color::Hue(i + ClrShift + imax / 6, imax, 0.3)); }
		if (x - 1 >= 0 && x - 1 < gfx.ScreenWidth && y >= 0 && y < gfx.ScreenHeight) { gfx.PutPixel(x - 1, y, Color::Hue(i + ClrShift + imax / 6, imax, 0.3)); }
		if (x >= 0 && x < gfx.ScreenWidth && y + 1 >= 0 && y + 1 < gfx.ScreenHeight) { gfx.PutPixel(x, y + 1, Color::Hue(i + ClrShift + imax / 6, imax, 0.3)); }
		if (x >= 0 && x < gfx.ScreenWidth && y - 1 >= 0 && y - 1 < gfx.ScreenHeight) { gfx.PutPixel(x, y - 1, Color::Hue(i + ClrShift + imax / 6, imax, 0.3)); }

		if (i == 0) {
			x1 = x;
			x2 = x;
			y1 = y;
			y2 = y;
		}
		else {
			if (x < x1) { x1 = x; }
			if (x > x2) { x2 = x; }
			if (y < y1) { y1 = y; }
			if (y > y2) { y2 = y; }
		}
	}

	for (int i = 0; i < imax; i++) {
		int temp = i;
		double x = initX;
		double y = initY;
		double dir = initDir;
		double step = initStep;
		int pwr2 = imax;
		for (int digitOrder = 0; digitOrder < lvl; digitOrder++) {
			pwr2 /= 2;
			bool digitVal = (temp >= pwr2);
			temp %= pwr2;

			if (digitVal) { dir += dirStep1; }
			else { dir += dirStep2; }
			x += (step * sin(dir));
			y += (step * cos(dir));

			step *= stepCoef;
			if (digitVal) { step *= leftStepCoef; }

		}
		if (x >= 0 && x < gfx.ScreenWidth && y >= 0 && y < gfx.ScreenHeight) { gfx.PutPixel(x, y, Color::Hue(i + ClrShift, imax)); }

	}


	dirStep1 += 0.005;
	dirStep2 += 0.0002;
	initDir -= (0.01*(1+sin(dirStep2*40.351)));
	ClrShift += 30;

	if (stepCoefUp) { stepCoef += 0.0002; }
	else { stepCoef -= 0.0002; }
	if (stepCoef > 0.85) { 
		stepCoef = 0.85; 
		stepCoefUp = false; 
	}
	if (stepCoef < 0.6) { 
		stepCoef = 0.6; 
		stepCoefUp = true; 
	}



	if (x2 + margin > gfx.ScreenWidth) {vx -= a;}
	if (x1 - margin < 0) {vx += a;}
	if (y2 + margin > gfx.ScreenHeight) {vy -= a;}
	if (y1 - margin < 0) {vy += a;}
	if (x2 + marginROT > gfx.ScreenWidth) {vy -= aROT;}
	if (x1 - marginROT < 0) {vy += aROT;}
	if (y2 + marginROT > gfx.ScreenHeight) {vx += aROT;}
	if (y1 - marginROT < 0) {vx -= aROT;}

	vx += g * sin(dirStep2*7.1);
	vy += g * cos(dirStep2*7.1);

	if (vx > vMax) { vx = vMax; }
	if (vx < -vMax) { vx = -vMax; }
	if (vy > vMax) { vy = vMax; }
	if (vy < -vMax) { vy = -vMax; }
	vx *= friction;
	vy *= friction;



	initX += vx;
	initY += vy;

#ifndef NDEBUG
	DrawRect(x1, x2, y1, y2);
	Text txt = Text("x1="+Text::ToSrtring(int(x1)), fnt);
	srf = txt.GetSurface();
	gfx.DrawSprite(0, 0, srf);
	txt = Text("x2=" + Text::ToSrtring(int(x2)), fnt);
	srf = txt.GetSurface();
	gfx.DrawSprite(0, 20, srf);
	txt = Text("y1=" + Text::ToSrtring(int(y1)), fnt);
	srf = txt.GetSurface();
	gfx.DrawSprite(0, 40, srf);
	txt = Text("y2=" + Text::ToSrtring(int(y2)), fnt);
	srf = txt.GetSurface();
	gfx.DrawSprite(0, 60, srf);
	txt = Text("stepCoef=" + Text::ToSrtring(stepCoef, 3), fnt);
	srf = txt.GetSurface();
	gfx.DrawSprite(0, 80, srf);
	txt = Text("leftStepCoef=" + Text::ToSrtring(leftStepCoef, 3), fnt);
	srf = txt.GetSurface();
	gfx.DrawSprite(0, 100, srf);
#endif

}

int Game::pwr(int x, int y) {
	int r = 1;
	for (int i = 0; i < y; i++) {
		r *= x;
	}
	return r;
}
int Game::pwr(int y) {
	int r = 1;
	for (int i = 0; i < y; i++) {
		r *= 2;
	}
	return r;
}
void Game::DrawRect(int x1, int x2, int y1, int y2) {
	for (int i = x1; i <= x2; i++) {
		if (i >= 0 && i < gfx.ScreenWidth && y1 >= 0 && y1 < gfx.ScreenHeight) {
			gfx.PutPixel(i, y1, 255, 255, 255);
		}
		if (i >= 0 && i < gfx.ScreenWidth && y2 >= 0 && y2 < gfx.ScreenHeight) {
			gfx.PutPixel(i, y2, 255, 255, 255);
		}
	}
	for (int j = y1; j <= y2; j++) {
		if (x1 >= 0 && x1 < gfx.ScreenWidth && j >= 0 && j < gfx.ScreenHeight) {
			gfx.PutPixel(x1, j, 255, 255, 255);
		}
		if (x2 >= 0 && x2 < gfx.ScreenWidth && j >= 0 && j < gfx.ScreenHeight) {
			gfx.PutPixel(x2, j, 255, 255, 255);
		}
	}
}
