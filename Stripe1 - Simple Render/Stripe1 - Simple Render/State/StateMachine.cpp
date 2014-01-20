#include "../Game.h"

CStateMachine::CStateMachine()
{
	m_bIsStarted = false;

	// Damos acceso global a esta instancia
	StateMachine = this;
}

CStateMachine::~CStateMachine()
{
	StateMachine = NULL;
}

void CStateMachine::Start()
{
	m_bIsStarted = true;

	// Aquí inicializaremos el estado default
}

void CStateMachine::DoFrame()
{
	if (m_bIsStarted)
	{
		Graphics->ClearScreen(0, 255, 255);

		// Aquí dibujaremos el state actual

		Graphics->SwapBuffers();
	}
}