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
	
	void SetPositionY(float y);
	void MoveForward();
	void MoveBackward();
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	void RotateOverXPositive();
	void RotateOverXNegative();
	void RotateOverYPositive();
	void RotateOverYNegative();
	void RotateOverZPositive();
	void RotateOverZNegative();
	void Update();

private:
	void TranslateCamera(XMVECTOR vector);
	void RotateCamera(XMVECTOR axisVector, float angle);
	void RotateMovement(XMVECTOR q);

	// Estructura que contiene los ejes de movimiento de la camara
	struct Movement
	{
		XMVECTOR xVelocity;
		XMVECTOR yVelocity;
		XMVECTOR zVelocity;
	};

	// Velocidad de rotacion sobre cada eje
	XMFLOAT3 rotationVelocity;

	// Velocidad de movimiento sobre cada eje
	Movement movementVelocity;



	XMVECTOR m_vEye,
			 m_vLookAt,
			 m_vUp;

	XMMATRIX m_mxView;
	XMMATRIX m_mxProjection;
};

#endif