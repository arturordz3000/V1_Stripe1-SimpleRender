#ifndef _CACTORBUMPEDCUBE_H_
#define _CACTORBUMPEDCUBE_H_

#include "../Game.h"

class CActorBumpedCube : public CActor
{
public:

	CActorBumpedCube();
	~CActorBumpedCube();

	void OnLoad();
	void Update();
	void Draw();

private:
	ID3D11ShaderResourceView* normalMap;
};

#endif