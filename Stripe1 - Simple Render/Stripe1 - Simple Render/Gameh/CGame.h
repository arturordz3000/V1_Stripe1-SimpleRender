#ifndef _CGAME_H_
#define _CGAME_H_

#include "../Game.h"
#include "../Graphics.h"
#include "../State.h"

extern class CGame *Game;
extern CGraphics *Graphics;
extern CCamera *Camera;
extern CStateMachine *StateMachine;

class CGame
{
public:

	CGame();
	~CGame();

	int Run();
	void Exit();

private:
	
	CGraphics *m_pGraphics;
	CCamera *m_pCamera;
	CStateMachine *m_pStateMachine;

	bool m_bIsRunning;
};

#endif