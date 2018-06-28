
#include "MainWindow.h"
#include "Game.h"
#include <string>


Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(std::random_device()()),
	hxg(70,7,12, true)
	//hxg(100,3,3, true)
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
	pM = M;
	M = wnd.mouse.LeftIsPressed();
	pSpace = Space;
	Space = wnd.kbd.KeyIsPressed(VK_SPACE);

	if (!pSpace && Space) {
		State = (State + 1) % 3;
	}

	if (!pM && M) {
		if (State == 1) { hxg.AddOrRemoveConnection(wnd.mouse.GetFloatPos()); }
		if (State == 2) { hxg.Rot(wnd.mouse.GetFloatPos()); }
	}

}

void Game::ComposeFrame()
{
	if (State == 0) { hxg.Draw(gfx, wnd.mouse.GetFloatPos()); }
	if (State == 1) { hxg.DrawSideHover(gfx, wnd.mouse.GetFloatPos()); }
	if (State == 2) { hxg.DrawHover(gfx, wnd.mouse.GetFloatPos()); }
}
