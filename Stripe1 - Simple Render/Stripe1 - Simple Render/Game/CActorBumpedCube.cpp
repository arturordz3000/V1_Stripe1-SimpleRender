#include "../Game.h"
#include "../Structs.h"

void CActorBumpedCube::OnLoad()
{
	HRESULT d3dResult = D3DX11CreateShaderResourceViewFromFile( Graphics->GetDevice(), L"Textures\\pn.gif", 0, 0, &normalMap, 0 );
	this->mxWorld = XMMatrixIdentity();
}

CActorBumpedCube::CActorBumpedCube()
{
	this->OnLoad();
}

CActorBumpedCube::~CActorBumpedCube()
{

}

void CActorBumpedCube::Update()
{
	static float fRotationX;
	static float fRotationY;

	fRotationX += .001f;
	fRotationY += .001f;

	this->mxWorld = XMMatrixRotationY( fRotationY ) * XMMatrixRotationX( fRotationX );
}

void CActorBumpedCube::Draw()
{
	BumpedBuffer sMatrixBuffer;
	sMatrixBuffer.m_mxWorld = XMMatrixTranspose( this->mxWorld );
	sMatrixBuffer.m_mxView = XMMatrixTranspose( Camera->GetViewMatrix() );
	sMatrixBuffer.m_mxProjection = XMMatrixTranspose( Camera->GetProjectionMatrix() );
	sMatrixBuffer.m_f3CameraPosition = XMFLOAT3(Camera->GetPosition().x, Camera->GetPosition().y, Camera->GetPosition().z);
	Graphics->GetDeviceContext()->UpdateSubresource( this->m_pResources->d3dConstantBuffer, 0, NULL, &sMatrixBuffer, 0, 0 );

	//
	// Renderea un cubo
	//
	UINT uiStride = sizeof( BumpedVertex );
	UINT uiOffset = 0;

	Graphics->GetDeviceContext()->IASetVertexBuffers( 0, 1,  &this->m_pResources->d3dVertexBuffer, &uiStride, &uiOffset );
	Graphics->GetDeviceContext()->IASetInputLayout(this->m_pResources->d3dInputLayout);
	Graphics->GetDeviceContext()->IASetIndexBuffer( this->m_pResources->d3dIndexBuffer, DXGI_FORMAT_R16_UINT, 0 );
	Graphics->GetDeviceContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	Graphics->GetDeviceContext()->VSSetShader( this->m_pResources->d3dVertexShader, NULL, 0 );
	Graphics->GetDeviceContext()->VSSetConstantBuffers( 0, 1, &this->m_pResources->d3dConstantBuffer );
	Graphics->GetDeviceContext()->PSSetShader(this->m_pResources->d3dPixelShader, NULL, 0 );
	Graphics->GetDeviceContext()->PSSetShaderResources( 0, 1, &this->m_pResources->d3dTexture );	
	Graphics->GetDeviceContext()->PSSetShaderResources( 1, 1, &this->normalMap );
	Graphics->GetDeviceContext()->PSSetSamplers( 0, 1, &this->m_pResources->d3dSampler );
	Graphics->GetDeviceContext()->DrawIndexed( 36, 0, 0 );
}