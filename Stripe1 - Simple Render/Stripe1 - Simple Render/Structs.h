#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include "Game.h"

struct SimpleVertex
{
	XMFLOAT3 m_f3Position;
	XMFLOAT4 m_f4Color;
};

struct TexturedVertex
{
	XMFLOAT3 m_f3Position;
	XMFLOAT2 m_f2UV;
};

struct TerrainVertex
{
	XMFLOAT3 pos;
	XMFLOAT2 uv;
	XMFLOAT2 blendUV;
	XMFLOAT3 normal;
};

struct MatrixBuffer
{
	XMMATRIX m_mxWorld;
	XMMATRIX m_mxView;
	XMMATRIX m_mxProjection;
};

struct TerrainConstantBuffer
{
	XMMATRIX m_mxWorld;
	XMMATRIX m_mxView;
	XMMATRIX m_mxProjection;	
};

#endif