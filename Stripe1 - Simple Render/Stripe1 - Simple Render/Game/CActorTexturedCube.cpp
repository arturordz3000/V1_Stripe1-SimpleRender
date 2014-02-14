#include "../Game.h"
#include "../Structs.h"

void CActorTexturedCube::OnLoad()
{
	this->mxWorld = XMMatrixIdentity();
}

CActorTexturedCube::CActorTexturedCube()
{
	this->OnLoad();
}

CActorTexturedCube::~CActorTexturedCube()
{

}

void CActorTexturedCube::Update()
{
	static float fRotationX;
	static float fRotationY;

	if (Input->IsKeyDown(VK_RIGHT))
		fRotationX += .1f;

	if (Input->IsKeyDown(VK_LEFT))
		fRotationX -= .1f;

	if (Input->IsKeyDown(VK_UP))
		fRotationY += .1f;

	if (Input->IsKeyDown(VK_DOWN))
		fRotationY -= .1f;

	this->mxWorld = XMMatrixRotationY( fRotationY ) * XMMatrixRotationX( fRotationX );
}

void CActorTexturedCube::Draw()
{
	MatrixBuffer sMatrixBuffer;
	sMatrixBuffer.m_mxWorld = XMMatrixTranspose( this->mxWorld );
	sMatrixBuffer.m_mxView = XMMatrixTranspose( Camera->GetViewMatrix() );
	sMatrixBuffer.m_mxProjection = XMMatrixTranspose( Camera->GetProjectionMatrix() );
	Graphics->GetDeviceContext()->UpdateSubresource( this->m_pResources->d3dConstantBuffer, 0, NULL, &sMatrixBuffer, 0, 0 );

	//
	// Renderea un cubo
	//
	UINT uiStride = sizeof( TexturedVertex );
	UINT uiOffset = 0;

	Graphics->GetDeviceContext()->IASetVertexBuffers( 0, 1,  &this->m_pResources->d3dVertexBuffer, &uiStride, &uiOffset );
	Graphics->GetDeviceContext()->IASetInputLayout(this->m_pResources->d3dInputLayout);
	Graphics->GetDeviceContext()->IASetIndexBuffer( this->m_pResources->d3dIndexBuffer, DXGI_FORMAT_R16_UINT, 0 );
	Graphics->GetDeviceContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	Graphics->GetDeviceContext()->VSSetShader( this->m_pResources->d3dVertexShader, NULL, 0 );
	Graphics->GetDeviceContext()->VSSetConstantBuffers( 0, 1, &this->m_pResources->d3dConstantBuffer );
	Graphics->GetDeviceContext()->PSSetShader(this->m_pResources->d3dPixelShader, NULL, 0 );
	Graphics->GetDeviceContext()->PSSetShaderResources( 0, 1, &this->m_pResources->d3dTexture );
	Graphics->GetDeviceContext()->PSSetSamplers( 0, 1, &this->m_pResources->d3dSampler );
	Graphics->GetDeviceContext()->DrawIndexed( 36, 0, 0 );
}