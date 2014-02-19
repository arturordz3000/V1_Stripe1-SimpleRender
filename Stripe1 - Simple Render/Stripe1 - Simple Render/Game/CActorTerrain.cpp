#include "../Game.h"

CActorTerrain::CActorTerrain()
{
	this->OnLoad();
}

CActorTerrain::~CActorTerrain()
{

}

void CActorTerrain::OnLoad()
{
	this->mxWorld = XMMatrixIdentity();
	HRESULT d3dResult = D3DX11CreateShaderResourceViewFromFile( Graphics->GetDevice(), L"Textures\\Mars.jpg", 0, 0, &colorMap2, 0 );
	d3dResult = D3DX11CreateShaderResourceViewFromFile( Graphics->GetDevice(), L"Textures\\GrandCanyon.png", 0, 0, &blendMap, 0 );
}

void CActorTerrain::Update()
{

}

void CActorTerrain::Draw()
{
	TerrainConstantBuffer sConstantBuffer;
	sConstantBuffer.m_mxWorld = XMMatrixTranspose( this->mxWorld );
	sConstantBuffer.m_mxView = XMMatrixTranspose( Camera->GetViewMatrix() );
	sConstantBuffer.m_mxProjection = XMMatrixTranspose( Camera->GetProjectionMatrix() );

	Graphics->GetDeviceContext()->UpdateSubresource( this->m_pResources->d3dConstantBuffer, 0, NULL, &sConstantBuffer, 0, 0 );

	//
	// Renderea un terreno
	//
	UINT uiStride = sizeof( TerrainVertex );
	UINT uiOffset = 0;

	Graphics->GetDeviceContext()->IASetVertexBuffers( 0, 1,  &this->m_pResources->d3dVertexBuffer, &uiStride, &uiOffset );
	Graphics->GetDeviceContext()->IASetInputLayout(this->m_pResources->d3dInputLayout);
	Graphics->GetDeviceContext()->IASetIndexBuffer( this->m_pResources->d3dIndexBuffer, DXGI_FORMAT_R32_UINT, 0 );
	Graphics->GetDeviceContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	Graphics->GetDeviceContext()->VSSetShader( this->m_pResources->d3dVertexShader, NULL, 0 );
	Graphics->GetDeviceContext()->VSSetConstantBuffers( 0, 1, &this->m_pResources->d3dConstantBuffer );
	Graphics->GetDeviceContext()->PSSetShader(this->m_pResources->d3dPixelShader, NULL, 0 );
	Graphics->GetDeviceContext()->PSSetShaderResources( 0, 1, &this->m_pResources->d3dTexture );
	Graphics->GetDeviceContext()->PSSetShaderResources( 1, 1, &colorMap2 );
	Graphics->GetDeviceContext()->PSSetShaderResources( 2, 1, &blendMap );
	Graphics->GetDeviceContext()->PSSetSamplers( 0, 1, &this->m_pResources->d3dSampler );
	Graphics->GetDeviceContext()->DrawIndexed( this->iIndexCount, 0, 0 );
}