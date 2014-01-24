#ifndef _CSTATEMAINGAME_H_
#define _CSTATEMAINGAME_H_

#include "../Game.h"

class CStateMainGame : public CState
{
public:

	CStateMainGame();
	~CStateMainGame();

	void DoFrame();

protected:

	void OnLoad();
};

#endif