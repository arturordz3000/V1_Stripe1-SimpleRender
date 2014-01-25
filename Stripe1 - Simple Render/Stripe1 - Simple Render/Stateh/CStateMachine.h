#ifndef _CSTATEMACHINE_H_
#define _CSTATEMACHINE_H_

#include "../Game.h"
#include "CState.h"

using namespace std;

class CStateMachine
{
public:

	CStateMachine();
	~CStateMachine();
	
	void Start(); // Se usará después
	void DoFrame();
	void ChangeState(string state);

private:

	bool m_bIsStarted;
	string m_strNextState;
	CState *m_pCurrentState;
};

#endif