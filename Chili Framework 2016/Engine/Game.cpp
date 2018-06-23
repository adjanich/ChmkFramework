
#include "MainWindow.h"
#include "Game.h"
#include <string>



Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	rng(std::random_device()())
{

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
		}
		if (x >= 0 && x < gfx.ScreenWidth && y >= 0 && y < gfx.ScreenHeight) { gfx.PutPixel(x, y, Color::Hue(i+ClrShift,imax)); }

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


	dirStep1 += 0.005;
	dirStep2 += 0.0002;
	initDir -= (0.005*(1+sin(dirStep2*40.351)));
	ClrShift += 30;

	if (stepCoefUp) { stepCoef += 0.0002; }
	else { stepCoef -= 0.0002; }
	if (stepCoef > 0.8) { 
		stepCoef = 0.8; 
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