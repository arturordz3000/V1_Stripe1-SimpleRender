#ifndef _CACTORMGR_H_
#define _CACTORMGR_H_

#include "../Game.h"
#include "CActor.h"

using namespace std;

class CActorMgr
{
public:

	CActorMgr();
	~CActorMgr();

	void UpdateActors();
	void DrawActors();
	void LoadActor(CActor *actor);
	void UnloadActors();

private:
	std::list<CActor*> m_lActors;
};

#endif