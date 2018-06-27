
#include "MainWindow.h"
#include "Game.h"
#include <string>


Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(std::random_device()()),
	hxg(50, 5, 7, true)
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
	hxg.Draw(gfx, wnd.mouse.GetFloatPos());
}
