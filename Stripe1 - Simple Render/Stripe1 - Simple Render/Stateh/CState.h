#ifndef _CSTATE_H_
#define _CSTATE_H_

#include "../Game.h"

using namespace std;

class CState
{
public:

	CState();
	~CState();

	virtual void DoFrame() = 0;

protected:

	virtual void OnLoad() = 0;
};

#endif