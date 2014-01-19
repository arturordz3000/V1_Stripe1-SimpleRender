#include "../Game.h"

CGame *Game			= NULL;
CGraphics *Graphics	= NULL;

CGame::CGame()
{
	// Damos acceso global a esta instancia
	Game = this;

	// Inicializamos el m�dulo Graphics
	m_pGraphics = new CGraphics();
}

CGame::~CGame()
{
	// Borramos todos los recursos utilizados

	Game = NULL;
	Graphics = NULL;

	delete m_pGraphics;
}

int CGame::Run()
{
	m_bIsRunning = true;

	// Inicializamos la ventana
	Graphics->InitWindow(600, 400, true);

	// Loop principal
	while (m_bIsRunning)
	{
		MSG msg;

		// Obtenemos los mensajes que mande el sistema operativo a
		// la aplicaci�n
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			// La aplicaci�n debe cerrarse
			if (msg.message == WM_QUIT)
				break;

			// Preparamos el mensaje recibido
			TranslateMessage(&msg);

			// Mandamos el mensaje a la funci�n WindowProc
			// definida en el archivo Utils.cpp
			DispatchMessage(&msg);
		}
		else
		{
			// Haremos render con DirectX despu�s
		}
	}

	return 0;
}

void CGame::Exit()
{
	this->m_bIsRunning = false;
}