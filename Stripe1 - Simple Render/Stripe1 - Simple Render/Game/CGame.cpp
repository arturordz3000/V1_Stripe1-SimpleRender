#include "../Game.h"

CGame *Game	= NULL;
CGraphics *Graphics	= NULL;
CCamera *Camera	= NULL;
CStateMachine *StateMachine = NULL;
CActorMgr *ActorMgr = NULL;
CInput *Input = NULL;
CResourceMgr *ResourceMgr = NULL;

CGame::CGame()
{
	m_bIsRunning = false;

	// Damos acceso global a esta instancia
	Game = this;

	// Inicializamos el módulo Graphics
	m_pGraphics = new CGraphics();

	// Inicializamos la cámara
	void *cameraPtr;
	size_t alignment = 16;
	size_t objectSize = sizeof(CCamera);

	cameraPtr = _aligned_malloc(objectSize, alignment);

	m_pCamera = new (cameraPtr) CCamera();

	// Inicializamos la máquina de estados
	m_pStateMachine = new CStateMachine();

	// Inicializamos el manejador de actores
	m_pActorMgr = new CActorMgr();

	// Inicializamos el input
	m_pInput = new CInput();

	// Inicializamos el manejador de recursos
	m_pResourcesMgr = new CResourceMgr();
}

CGame::~CGame()
{
	// Borramos todos los recursos utilizados

	Game = NULL;
	Graphics = NULL;
	Camera = NULL;
	StateMachine = NULL;
	ActorMgr = NULL;

	delete m_pGraphics;
	delete m_pCamera;
	delete m_pStateMachine;
	delete m_pActorMgr;
}

int CGame::Run()
{
	m_bIsRunning = true;

	// Inicializamos la ventana
	if(!Graphics->InitWindow(800, 600, true))
		m_bIsRunning = false;
	
	m_pStateMachine->Start();

	// Loop principal
	while (m_bIsRunning)
	{
		MSG msg;

		// Obtenemos los mensajes que mande el sistema operativo a
		// la aplicación
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			// El usuario cerró la aplicación
			if (msg.message == WM_QUIT)
				break;

			// Preparamos el mensaje recibido
			TranslateMessage(&msg);

			// Mandamos el mensaje a la función WindowProc
			// definida en el archivo Utils.cpp
			DispatchMessage(&msg);
		}
		else
		{
			m_pStateMachine->DoFrame();
		}
	}

	return 0;
}

void CGame::Exit()
{
	this->m_bIsRunning = false;
}