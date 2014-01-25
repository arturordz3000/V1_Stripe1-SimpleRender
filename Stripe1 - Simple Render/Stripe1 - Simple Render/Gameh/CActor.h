#ifndef _CACTOR_H_
#define _CACTOR_H_

#include "../Game.h"

class CActor
{
public:

	CActor();
	~CActor();

	virtual void OnLoad();
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	ID3D11VertexShader* d3dVertexShader;
	ID3D11PixelShader* d3dPixelShader;
	ID3D11InputLayout* d3dInputLayout;
	ID3D11Buffer* d3dVertexBuffer;
	ID3D11Buffer* d3dIndexBuffer;
	ID3D11Buffer* d3dConstantBuffer;
	XMFLOAT3 vTranslation;
	XMFLOAT3 vRotation;
	XMFLOAT3 vScale;
	XMMATRIX mxWorld;
};

#endif