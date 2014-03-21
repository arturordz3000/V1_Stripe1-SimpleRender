#ifndef _CACTORSKYBOX_H_
#define _CACTORSKYBOX_H_

#include "../Game.h"

class CActorSkyBox : public CActor 
{
public:
	CActorSkyBox();
	~CActorSkyBox();

	void OnLoad();
	void Update();
	void Draw();
};

#endif