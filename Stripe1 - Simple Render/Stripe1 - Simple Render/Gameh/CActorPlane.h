#ifndef _CACTORPLANE_H_
#define _CACTORPLANE_H_

#include "../Game.h"

class CActorPlane : public CActor
{
public:

	CActorPlane();
	~CActorPlane();

	void OnLoad();
	void Update();
	void Draw();
};

#endif

