#include "Game.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		Game->Exit();
		break;
	case WM_KEYDOWN:
		// Haremos código por aquí después
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}