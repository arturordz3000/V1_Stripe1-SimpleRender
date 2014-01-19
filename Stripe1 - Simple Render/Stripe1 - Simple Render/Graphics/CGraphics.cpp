#include "../Game.h"

LPCWSTR g_wStrWindowTitle = L"Stripe 1 - Simple Render";

CGraphics::CGraphics()
{
	// Damos acceso global a esta instancia
	Graphics = this;

	// Limpiamos las variables de DirectX
	m_d3dDevice = NULL;
	m_d3dDeviceContext = NULL;
	m_d3dRenderTarget = NULL;
	m_dxgSwapChain = NULL;
}

CGraphics::~CGraphics()
{
	Graphics = NULL;
}

void CGraphics::InitWindow(int iWidth, int iHeight, bool bWindowed)
{
	// Inicializamos las variables miembro de la clase
	m_bIsWindowed = bWindowed;
	m_iWidth = iWidth;
	m_iHeight = iHeight;

	DWORD dwWindowStyle;

	// Damos el estilo de la ventana dependiendo si es
	// en modo ventana o pantalla completa
	if (m_bIsWindowed)
		dwWindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	else
		dwWindowStyle = WS_POPUP | WS_VISIBLE;

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// Configuramos las propiedades de la ventana
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = (HBRUSH)NULL;
	wc.hCursor = LoadCursor(g_hInstance, IDC_ARROW);
	wc.hInstance = g_hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = L"LMADGameEngine";
	wc.lpszMenuName = NULL;
	wc.style = CS_OWNDC;

	// Registramos la ventana para que el sistema operativo
	// tenga conocimiento de ella
	RegisterClassEx(&wc);

	// Creamos la ventana en memoria
	m_hWnd = CreateWindowEx(
		NULL, 
		L"LMADGameEngine", 
		g_wStrWindowTitle, 
		dwWindowStyle, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT,
		m_iWidth, 
		m_iHeight,
		NULL,
		NULL,
		g_hInstance,
		NULL);

	// Voila!
	ShowWindow(m_hWnd, g_nCmdShow);


}