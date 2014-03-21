#ifndef _CSTATEMAINGAME_H_
#define _CSTATEMAINGAME_H_

#include "../Game.h"

class CStateMainGame : public CState
{

private:
	unsigned int uiTexturedCubeResourcesId;
	unsigned int uiTerrainResourcesId;
	unsigned int uiBumpedCubeResourcesId;
	unsigned int uiSkuBoxResourcesId;

	ID3D11DepthStencilView *d3dDepthStencilView;

	void InitializeResources();

public:

	CStateMainGame();
	~CStateMainGame();

	void DoFrame();

protected:

	void OnLoad();
};

#endif