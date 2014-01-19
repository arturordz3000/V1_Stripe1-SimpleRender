#ifndef _CGRAPHICS_H_
#define _CGRAPHICS_H_

#include "../Game.h"

class CGraphics
{
public:
	
	CGraphics();
	~CGraphics();

	void InitWindow(int iWidth, int iHeight, bool bWindowed);
	int GetWidth() { return m_iWidth; }
	int GetHeight() { return m_iHeight; }

private:

	// Dimensiones de la ventana cliente
	int m_iWidth, m_iHeight;

	// Manejador de pantalla completa
	bool m_bIsWindowed;

	// Interfaces de DirectX
	ID3D11Device *m_d3dDevice;
	ID3D11DeviceContext *m_d3dDeviceContext;
	IDXGISwapChain *m_dxgSwapChain;	
	ID3D11RenderTargetView *m_d3dRenderTarget;

	// Manejador de la ventana
	HWND m_hWnd;
};

#endif