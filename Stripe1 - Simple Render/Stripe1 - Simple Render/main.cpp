#include "Game.h"
HINSTANCE g_hInstance;
int g_nCmdShow;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CGame *game = new CGame();
	g_hInstance = hInstance;
	g_nCmdShow = nCmdShow;
	game->Run();
	delete game;

	return 0;
}