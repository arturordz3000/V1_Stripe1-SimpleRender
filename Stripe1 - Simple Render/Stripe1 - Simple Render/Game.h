#ifndef _GAME_H_
#define _GAME_H_

#define _XM_NO_INTRINSICS_

#include <Windows.h>
#include <iostream>
#include <d3d11.h>
#include <d3dx11.h>
#include <xnamath.h>
#include <d3dcompiler.h>
#include <list>

#include "Gameh/CGame.h"
#include "Gameh/CActor.h"
#include "Gameh/CActorPlane.h"
#include "Gameh/CActorTexturedCube.h"
#include "Gameh/CActorTerrain.h"
#include "Gameh/CActorBumpedCube.h"
#include "Gameh/CActorSkyBox.h"
#include "Gameh/CActorMgr.h"
#include "Managersh/CResourceMgr.h"
#include "Graphics.h"
#include "State.h"
#include "Structs.h"
#include "Input.h"

extern HINSTANCE g_hInstance;
extern int g_nCmdShow;
extern LPCWSTR g_wStrWindowTitle;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif