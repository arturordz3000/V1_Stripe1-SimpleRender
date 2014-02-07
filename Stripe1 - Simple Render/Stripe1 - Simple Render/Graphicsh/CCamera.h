#ifndef _CCAMERA_H_
#define _CCAMERA_H_

#include "../Game.h"

__declspec(align(16)) class CCamera
{
public:

	CCamera();
	~CCamera();

	XMVECTOR GetPosition() { return m_vEye; }
	XMVECTOR GetTarget() { return m_vLookAt; }
	XMVECTOR SetPosition(XMVECTOR vPosition) { m_vEye = vPosition; }
	XMVECTOR SetTarget(XMVECTOR vTarget) { m_vLookAt = vTarget; }
	XMMATRIX GetViewMatrix();
	XMMATRIX GetProjectionMatrix() { return m_mxProjection; }

private:

	XMVECTOR m_vEye,
			 m_vLookAt,
			 m_vUp;

	XMMATRIX m_mxView;
	XMMATRIX m_mxProjection;
};

#endif