
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
	if (wnd.kbd.KeyIsPressed(VK_UP)) {
		x *= 641;
	
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
		x *= 6700417;
	}
}

void Game::ComposeFrame()
{
	Text txt = Text(Text::ToSrtring(x),fnt);
	gfx.DrawSprite(0,0,txt.GetSurface());
}
