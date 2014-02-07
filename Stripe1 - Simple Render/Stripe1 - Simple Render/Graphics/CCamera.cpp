#include "../Game.h"

CCamera::CCamera()
{
	// Inicializamos los par�metros de nuestra c�mara
	ZeroMemory(&m_vUp, sizeof(XMVECTOR));
	m_vUp = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
	m_vEye = XMVectorSet( 0.0f, 1.0f, -5.0f, 0.0f );
	m_vLookAt = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );

	m_mxProjection = XMMatrixPerspectiveFovLH( XM_PIDIV2, Graphics->GetWidth() / (FLOAT)Graphics->GetHeight(), 0.01f, 100.0f );

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