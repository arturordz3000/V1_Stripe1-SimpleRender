#include "../Game.h"
#include "../Structs.h"

void CActorSkyBox::OnLoad()
{
	this->mxWorld = XMMatrixIdentity();
}

CActorSkyBox::CActorSkyBox()
{
	this->OnLoad();
}

CActorSkyBox::~CActorSkyBox()
{

}

void CActorSkyBox::Update()
{
	
}

void CActorSkyBox::Draw()
{
	Graphics->DisableDepth();

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

	Graphics->EnableDepth();
}