#ifndef _CGRAPHICS_H_
#define _CGRAPHICS_H_

#include "../Game.h"

class CGraphics
{
public:
	
	CGraphics();
	~CGraphics();

	bool InitWindow(const int &iWidth, const int &iHeight, const bool &bWindowed);
	bool InitGraphicsMode();
	void ClearScreen(const int &iR, const int &iG, const int &iB);
	void SwapBuffers();
	HRESULT CompileShaderFromFile( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut );
	int GetWidth() { return m_iWidth; }
	int GetHeight() { return m_iHeight; }
	ID3D11Device *GetDevice() { return m_d3dDevice; }
	ID3D11DeviceContext *GetDeviceContext() { return m_d3dDeviceContext; }
	D3D_DRIVER_TYPE GetDriverType() { return m_d3dDriverType; }
	D3D_FEATURE_LEVEL GetFeatureLevel() { return m_d3dFeatureLevel; }

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

	ID3D11Texture2D* m_d3dDepthTexture;
	ID3D11DepthStencilView* m_d3dDepthStencilView;
	ID3D11DepthStencilState* m_d3dDepthStencilState;

	// Tipo de driver de Direct3D
	D3D_DRIVER_TYPE m_d3dDriverType;

	// Feature Level de Direct3D
	D3D_FEATURE_LEVEL m_d3dFeatureLevel;

	// Manejador de la ventana
	HWND m_hWnd;
};

#endif