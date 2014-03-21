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

bool CGraphics::InitWindow(const int &iWidth, const int &iHeight, const bool &bWindowed)
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

	// Inicializamos Direct3D
	if (!InitGraphicsMode())
		return false;

	// Voila!
	ShowWindow(m_hWnd, g_nCmdShow);

	return true;
}

bool CGraphics::InitGraphicsMode()
{
	// Esta variable la usaremos para ver el resultado de todas
	// las inicializaciones que hagamos
	HRESULT hResult;

	// Inicializamos los driver types.
	/**
	*	Un driver type es la forma en la que el PC ejecutará Direct3D.
	*	HARDWARE: Es la forma más rapida ya que corre directamente sobre la tarjeta gráfica.
	*			  Sólo puede ser usada si el hardware la soporta.
	*	WARP:	  Más lenta el HARDWARE. Esta emula las funcionalidades de Direct3D con
	*			  código bastante bien optimizado y es una buena opción a usar
	*			  si la PC donde se corre no tiene el hardware necesario.
	*	SOFTWARE: Permite al desarrollador crear su propio software para rendering
	*			  usando funcionalidad de Direct3D. Es la más lenta de las opciones.
	*	REFERENCE:Lleva a cabo las funcionalidades del hardware dentro del CPU cuando
	*			  los usuarios que no tienen el soporte para dicho hardware.
	**/
	D3D_DRIVER_TYPE d3dDriverTypes[] =
	{ D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE, D3D_DRIVER_TYPE_REFERENCE };
	int iDriverTypesCount = ARRAYSIZE(d3dDriverTypes);

	// Inicializamos los feature levels (versiones) de Direct3D
	D3D_FEATURE_LEVEL d3dFeatureLevels[] =
	{ D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };
	int iFeatureLevelCount = ARRAYSIZE(d3dFeatureLevels);

	// Creamos el descriptor del swap chain
	/**
	*	Un swap chain es un conjunto de buffers en donde
	*	la tarjeta gráfica está constantemente dibujando.
	*	En videojuegos, normalmente existen dos buffers llamados
	*	front y back buffer. El front buffer es el que se nos muestra
	*	en pantalla, mientras que el back buffer es donde la tarjeta
	*	gráfica está dibujando el frame que se dibujará a continuación.
	*
	*	Un descriptor (en DirectX) es una estructura para
	*	definir cómo queremos que se inicialice un objeto.
	**/
	DXGI_SWAP_CHAIN_DESC dxgSwapChainDesc;
	ZeroMemory(&dxgSwapChainDesc, sizeof(dxgSwapChainDesc));
	dxgSwapChainDesc.BufferCount = 1;
	dxgSwapChainDesc.BufferDesc.Width = m_iWidth;
	dxgSwapChainDesc.BufferDesc.Height = m_iHeight;
	dxgSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	dxgSwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	dxgSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	dxgSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	dxgSwapChainDesc.OutputWindow = m_hWnd;
	dxgSwapChainDesc.Windowed = m_bIsWindowed;
	dxgSwapChainDesc.SampleDesc.Count = 1;
	dxgSwapChainDesc.SampleDesc.Quality = 0;

	for (int i = 0; i < iDriverTypesCount; i++)
	{
		hResult = D3D11CreateDeviceAndSwapChain(
			NULL,
			d3dDriverTypes[i],
			NULL,
			NULL,
			d3dFeatureLevels,
			iFeatureLevelCount,
			D3D11_SDK_VERSION,
			&dxgSwapChainDesc,
			&m_dxgSwapChain,
			&m_d3dDevice,
			&m_d3dFeatureLevel,
			&m_d3dDeviceContext);

		if (SUCCEEDED(hResult))
		{
			m_d3dDriverType = d3dDriverTypes[i];
			break; // El device y swap chain han sido creados
		}
	}

	if (FAILED(hResult))
		return false; // No se pudo crear el device ni el swap chain

	// Textura que nos servirá como back buffer
	ID3D11Texture2D *d3dBackBufferTexture;

	// Ligamos nuestra textura con el back buffer del swap chain
	hResult = m_dxgSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&d3dBackBufferTexture);
	if (FAILED(hResult))
		return false; // Error al ligar nuestra textura con el back buffer

	// Indicamos al device que nuestra textura es donde deberá dibujar
	hResult = m_d3dDevice->CreateRenderTargetView(d3dBackBufferTexture, NULL, &m_d3dRenderTarget);
	if (d3dBackBufferTexture)
		d3dBackBufferTexture->Release();

	if (FAILED(hResult))
		return false; // No se pudo crear el render target

	// Ligamos el render target al pipe line de Direct3D
	//m_d3dDeviceContext->OMSetRenderTargets(1, &m_d3dRenderTarget, NULL);

	// Creamos el viewport
	D3D11_VIEWPORT d3dViewport;
	d3dViewport.Width = m_iWidth;
	d3dViewport.Height = m_iHeight;
	d3dViewport.MinDepth = 0.0f;
	d3dViewport.MaxDepth = 1.0f;
	d3dViewport.TopLeftX = 0.0f;
	d3dViewport.TopLeftY = 0.0f;

	m_d3dDeviceContext->RSSetViewports(1, &d3dViewport);

	D3D11_TEXTURE2D_DESC depthTexDesc;
	ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
	depthTexDesc.Width = m_iWidth;
	depthTexDesc.Height = m_iHeight;
	depthTexDesc.MipLevels = 1;
	depthTexDesc.ArraySize = 1;
	depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthTexDesc.SampleDesc.Count = 1;
	depthTexDesc.SampleDesc.Quality = 0;
	depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthTexDesc.CPUAccessFlags = 0;
	depthTexDesc.MiscFlags = 0;
		
	hResult = m_d3dDevice->CreateTexture2D(&depthTexDesc, NULL, &m_d3dDepthTexture);
	if(FAILED(hResult))
	{
		MessageBox(0, L"Error", L"Error al crear la DepthTexture", MB_OK);
		return false;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = depthTexDesc.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;

	hResult = m_d3dDevice->CreateDepthStencilView(m_d3dDepthTexture, &descDSV, &m_d3dDepthStencilView);
	if(FAILED(hResult))
	{
		MessageBox(0, L"Error", L"Error al crear el depth stencil target view", MB_OK);
		return false;
	}

	// Ligamos el render target al pipe line de Direct3D
	m_d3dDeviceContext->OMSetRenderTargets(1, &m_d3dRenderTarget, m_d3dDepthStencilView);

	D3D11_DEPTH_STENCIL_DESC descDSD;
	ZeroMemory(&descDSD, sizeof(descDSD));
	descDSD.DepthEnable = true;
	descDSD.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	descDSD.DepthFunc = D3D11_COMPARISON_LESS;
	descDSD.StencilEnable=true;
	descDSD.StencilReadMask = 0xFF;
	descDSD.StencilWriteMask = 0xFF;
	descDSD.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	descDSD.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	descDSD.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	descDSD.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	descDSD.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	descDSD.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	descDSD.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	descDSD.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	hResult = m_d3dDevice->CreateDepthStencilState(&descDSD, &m_d3dDepthStencilState);
	if(FAILED(hResult))
	{
		MessageBox(0, L"Error", L"Error al crear el depth stencil state", MB_OK);
		return false;
	}
	m_d3dDeviceContext->OMSetDepthStencilState(m_d3dDepthStencilState, 1);

	D3D11_DEPTH_STENCIL_DESC descDDSD;
	ZeroMemory(&descDDSD, sizeof(descDDSD));
	descDDSD.DepthEnable = false;
	descDDSD.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	descDDSD.DepthFunc = D3D11_COMPARISON_LESS;
	descDDSD.StencilEnable=true;
	descDDSD.StencilReadMask = 0xFF;
	descDDSD.StencilWriteMask = 0xFF;
	descDDSD.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	descDDSD.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	descDDSD.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	descDDSD.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	descDDSD.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	descDDSD.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	descDDSD.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	descDDSD.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	hResult = m_d3dDevice->CreateDepthStencilState(&descDDSD, &m_d3dDisabledDepthStencilState);
	if(FAILED(hResult))
	{
		MessageBox(0, L"Error", L"Error al crear el depth stencil state", MB_OK);
		return false;
	}

	return true;
}

void CGraphics::ClearScreen(const int &iR, const int &iG, const int &iB)
{
	float fNormalizer = 1.0f / 255.0f;
	float fUnitR = (float)iR * fNormalizer;
	float fUnitG = (float)iG * fNormalizer;
	float fUnitB = (float)iB * fNormalizer;

	float a_fClearColor[] = { fUnitR, fUnitG, fUnitB, 255 };

	m_d3dDeviceContext->ClearRenderTargetView(m_d3dRenderTarget, a_fClearColor);	
	m_d3dDeviceContext->ClearDepthStencilView( m_d3dDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );
}

void CGraphics::SwapBuffers()
{
	m_dxgSwapChain->Present(0, 0);
}

void CGraphics::DisableDepth()
{
	m_d3dDeviceContext->OMSetDepthStencilState(m_d3dDisabledDepthStencilState, 1);
}

void CGraphics::EnableDepth()
{
	m_d3dDeviceContext->OMSetDepthStencilState(m_d3dDepthStencilState, 1);
}

HRESULT CGraphics::CompileShaderFromFile( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut )
{
	HRESULT hr = S_OK;

		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	#if defined( DEBUG ) || defined( _DEBUG )
		// Sirve para que el shader proveea de información
		//para debugueo, pero sin afectar el rendimiento.
		dwShaderFlags |= D3DCOMPILE_DEBUG;
	#endif
		
		//Variable que se usa para obtener informacion
		//de errores y poder saber en dónde ocurrió
		//el error al compilar el shader
		ID3DBlob* pErrorBlob;

		//Compila el shader
		hr = D3DX11CompileFromFile( szFileName, NULL, NULL, szEntryPoint, szShaderModel, 
			dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL );

		if( FAILED(hr) )
		{
			if( pErrorBlob != NULL )
				OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );
			if( pErrorBlob ) pErrorBlob->Release();
			return hr;
		}
		if( pErrorBlob ) pErrorBlob->Release();

		return S_OK;
}