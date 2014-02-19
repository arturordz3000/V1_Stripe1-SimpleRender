#ifndef _CACTORTERRAIN_H_
#define _CACTORTERRAIN_H_

#include "../Game.h"

class CActorTerrain : public CActor
{
public:
	CActorTerrain();
	~CActorTerrain();

	void OnLoad();
	void Update();
	void Draw();

	int iIndexCount;

private:	
	ID3D11ShaderResourceView* colorMap2;
	ID3D11ShaderResourceView* blendMap;
};

#endif