#ifndef _GAME_H_
#define _GAME_H_

#include <Windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>

#include "Gameh/CGame.h"
#include "Graphics.h"

extern HINSTANCE g_hInstance;
extern int g_nCmdShow;
extern LPCWSTR g_wStrWindowTitle;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif