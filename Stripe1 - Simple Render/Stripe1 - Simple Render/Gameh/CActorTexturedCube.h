#ifndef _CACTORTEXTUREDCUBE_H_
#define _CACTORTEXTUREDCUBE_H_

#include "../Game.h"

class CActorTexturedCube : public CActor
{
public:

	CActorTexturedCube();
	~CActorTexturedCube();

	void OnLoad();
	void Update();
	void Draw();

private:	
	/*ID3D11SamplerState* d3dSamplerLinear;
	ID3D11ShaderResourceView* d3dTexture;*/
};

#endif