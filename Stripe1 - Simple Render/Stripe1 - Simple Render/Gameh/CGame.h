#ifndef _CGAME_H_
#define _CGAME_H_

#include "../Game.h"
#include "../Graphics.h"
#include "../State.h"
#include "../Input.h"
#include "CActorMgr.h"
#include "../Managersh/CResourceMgr.h"

extern class CGame *Game;
extern CGraphics *Graphics;
extern CCamera *Camera;
extern CStateMachine *StateMachine;
extern CActorMgr *ActorMgr;
extern CInput *Input;
extern CResourceMgr *ResourceMgr;

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
	CActorMgr *m_pActorMgr;
	CInput *m_pInput;
	CResourceMgr *m_pResourcesMgr;

	bool m_bIsRunning;
};

#endif