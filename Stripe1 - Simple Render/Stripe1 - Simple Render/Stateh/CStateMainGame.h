#ifndef _CSTATEMAINGAME_H_
#define _CSTATEMAINGAME_H_

#include "../Game.h"

class CStateMainGame : public CState
{

private:
	unsigned int uiTexturedCubeResourcesId;
	unsigned int uiTerrainResourcesId;
	unsigned int uiBumpedCubeResourcesId;

	void InitializeResources();

public:

	CStateMainGame();
	~CStateMainGame();

	void DoFrame();

protected:

	void OnLoad();
};

#endif