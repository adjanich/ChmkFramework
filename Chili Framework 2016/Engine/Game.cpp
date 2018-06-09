
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
	int x1;
	x1 = wnd.mouse.GetPosX();
	if (x1 > 800-30) { x1 = 800-30; }
	Text txt = Text("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.",fnt,800-x1);
	Surface txtsrf = txt.GetSurface();
	gfx.DrawSprite(x1,0,txtsrf);
}

void Game::ComposeFrame()
{

}
