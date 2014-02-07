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

struct MatrixBuffer
{
	XMMATRIX m_mxWorld;
	XMMATRIX m_mxView;
	XMMATRIX m_mxProjection;
};

#endif