
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

			if (digitVal) { dir += dirStep; }
			else { dir -= dirStep; }
			x += (step * sin(dir));
			y += (step * cos(dir));

			step *= stepCoef;
		}
		if (x >= 0 && x < gfx.ScreenWidth && y >= 0 && y < gfx.ScreenHeight) { gfx.PutPixel(x, y, Color::Hue(i+ClrShift,imax)); }
	}


	dirStep += 0.005;
	ClrShift += 30;
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