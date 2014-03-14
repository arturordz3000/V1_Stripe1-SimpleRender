#include "../Game.h"

CCamera::CCamera()
{
	XMFLOAT3 movementVelocity = XMFLOAT3(1.0f, 1.0f, 1.0f);
	XMFLOAT3 rotationVelocity =  XMFLOAT3(.05f, .05f, .05f);

	// Inicializamos los parámetros de nuestra cámara
	this->movementVelocity.xVelocity = XMLoadFloat3( &XMFLOAT3(movementVelocity.x, 0, 0) );
	this->movementVelocity.yVelocity = XMLoadFloat3( &XMFLOAT3(0, movementVelocity.y, 0) );
	this->movementVelocity.zVelocity = XMLoadFloat3( &XMFLOAT3(0, 0, movementVelocity.z) );
	this->rotationVelocity = rotationVelocity;

	// Cámara para terreno
	m_vUp = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
	m_vEye = XMVectorSet( 0.0f, 50.0f, 0.0f, 0.0f );
	m_vLookAt = XMVectorSet( 0.0f, 50.0f, 1.0f, 0.0f );

	m_mxProjection = XMMatrixPerspectiveFovLH( XM_PIDIV2, Graphics->GetWidth() / (FLOAT)Graphics->GetHeight(), 0.01f, 1000.0f );

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
	m_vLookAt = m_vEye + movementVelocity.zVelocity;
	m_mxView = XMMatrixLookAtLH(m_vEye, m_vLookAt, m_vUp);
	return m_mxView;
}

/**
* Traslada la camara sumandole el vector dado.
*
* PARAMETROS:
*
* vector: El vector a sumar
*
**/
void CCamera::TranslateCamera(XMVECTOR vector)
{
	m_vEye.x += vector.x;
	m_vEye.y += vector.y;
	m_vEye.z += vector.z;
}

/**
* Rota la camara alrededor del vector indicado.
*
* PARAMETROS: 
*
* axisVector: El vector sobre el cual girar la camara
* angle: Angulo de rotacion
*
**/
void CCamera::RotateCamera(XMVECTOR axisVector, float angle)
{
	// Obtengo el cuaternio de rotacion
	XMVECTOR rotationQuaternion = XMQuaternionRotationAxis(axisVector, angle);

	// Roto los ejes de movimiento de la camara
	RotateMovement(rotationQuaternion);
}

void CCamera::RotateMovement(XMVECTOR q)
{
	// Roto el eje de movimiento en X
	movementVelocity.xVelocity = XMVector3Rotate(movementVelocity.xVelocity, q);

	// Roto el eje de movimiento en Y
	movementVelocity.yVelocity = XMVector3Rotate(movementVelocity.yVelocity, q);

	// Roto el eje de movimiento en Z
	movementVelocity.zVelocity = XMVector3Rotate(movementVelocity.zVelocity, q);
}

void CCamera::SetPositionY(float y)
{
	this->m_vEye.y = y;
}

void CCamera::MoveForward()
{
	this->TranslateCamera(movementVelocity.zVelocity);
}

void CCamera::MoveBackward()
{
	this->TranslateCamera(-movementVelocity.zVelocity);
}

void CCamera::MoveRight()
{
	this->TranslateCamera(movementVelocity.xVelocity);
}

void CCamera::MoveLeft()
{
	this->TranslateCamera(-movementVelocity.xVelocity);
}

void CCamera::MoveUp()
{
	this->TranslateCamera(movementVelocity.yVelocity);
}

void CCamera::MoveDown()
{
	this->TranslateCamera(-movementVelocity.yVelocity);
}

void CCamera::RotateOverXPositive()
{
	this->RotateCamera(movementVelocity.xVelocity, rotationVelocity.x);
}

void CCamera::RotateOverXNegative()
{
	this->RotateCamera(movementVelocity.xVelocity, -rotationVelocity.x);
}

void CCamera::RotateOverYPositive()
{
	this->RotateCamera(XMLoadFloat3( &XMFLOAT3(0.0f, 1.0f, 0.0f) ), rotationVelocity.y);
}

void CCamera::RotateOverYNegative()
{
	this->RotateCamera(XMLoadFloat3( &XMFLOAT3(0.0f, 1.0f, 0.0f) ), -rotationVelocity.y);
}

void CCamera::RotateOverZPositive()
{
	this->RotateCamera(movementVelocity.zVelocity, rotationVelocity.z);
}

void CCamera::RotateOverZNegative()
{
	this->RotateCamera(movementVelocity.zVelocity, -rotationVelocity.z);
}

void CCamera::Update()
{
	if (Input->IsKeyDown(VK_UP))
		this->RotateOverXPositive();

	if (Input->IsKeyDown(VK_DOWN))
		this->RotateOverXNegative();

	if (Input->IsKeyDown(VK_RIGHT))
		this->RotateOverYPositive();

	if (Input->IsKeyDown(VK_LEFT))
		this->RotateOverYNegative();

	if (Input->IsKeyDown('w') || Input->IsKeyDown('W'))
		this->MoveForward();

	if (Input->IsKeyDown('s') || Input->IsKeyDown('S'))
		this->MoveBackward();

	if (Input->IsKeyDown('a') || Input->IsKeyDown('A'))
		this->MoveLeft();

	if (Input->IsKeyDown('d') || Input->IsKeyDown('D'))
		this->MoveRight();

	if (Input->IsKeyDown('q') || Input->IsKeyDown('Q'))
		this->MoveUp();

	if (Input->IsKeyDown('z') || Input->IsKeyDown('Z'))
		this->MoveDown();
}