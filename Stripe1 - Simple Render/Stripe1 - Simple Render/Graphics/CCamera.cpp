#include "../Game.h"

CCamera::CCamera()
{
	// Inicializamos los parámetros de nuestra cámara
	m_vUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	m_vEye = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	m_vLookAt = XMVectorSet(0.0f, 0.0f, 0.1f, 0.0f);

	// Damos acceso global a esta instancia
	Camera = this;
}

CCamera::~CCamera()
{
	Camera = NULL;
}

XMMATRIX CCamera::GetViewMatrix()
{
	// Actualizamos la matriz View para que pueda utilizarse
	// en el renderizado de la escena
	m_mxView = XMMatrixLookAtLH(m_vEye, m_vLookAt, m_vUp);
	return m_mxView;
}