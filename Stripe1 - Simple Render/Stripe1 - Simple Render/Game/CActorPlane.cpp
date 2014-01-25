#include "../Game.h"
#include "../Structs.h"

void CActorPlane::OnLoad()
{
	ID3DBlob* d3dVertexShaderBlob = NULL;
	HRESULT hResult = Graphics->CompileShaderFromFile(L"SimpleShader.fx", "VS", "vs_4_0", &d3dVertexShaderBlob);

	if (FAILED(hResult)) {
		MessageBox(NULL,
            L"No se pudo compilar shader.", L"Error", MB_OK );
		Game->Exit();
	}

	// Se crea el vertex shader
	hResult = Graphics->GetDevice()->CreateVertexShader( d3dVertexShaderBlob->GetBufferPointer(), d3dVertexShaderBlob->GetBufferSize(), NULL, &this->d3dVertexShader );
	if( FAILED( hResult ) )
	{	
		d3dVertexShaderBlob->Release();
		Game->Exit();
	}

	// Define cómo entrarán
	// los datos al shader
	D3D11_INPUT_ELEMENT_DESC a_d3dLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },

		//El 12 de aquí indica el número de bytes que hay entre
		//el comienzo del buffer y los datos a los que se hace
		//la referencia. Por ejemplo, hay un Vector de 3 elementos
		//de tipo flotante. Los float son de 4 bytes, entonces 4x3=12
		//y es por eso que se pone aquí un 12, que es donde comienza
		//el vector de color.
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	UINT numElements = ARRAYSIZE( a_d3dLayout );

	//Se crea el input layout
	hResult = Graphics->GetDevice()->CreateInputLayout( a_d3dLayout, numElements, d3dVertexShaderBlob->GetBufferPointer(),
		d3dVertexShaderBlob->GetBufferSize(), &this->d3dInputLayout );

	//Ya no se ocupará
	d3dVertexShaderBlob->Release();
	if(FAILED(hResult))
		Game->Exit();

	Graphics->GetDeviceContext()->IASetInputLayout(this->d3dInputLayout);

	ID3DBlob* d3dPixelShaderBlob = NULL;
	hResult = Graphics->CompileShaderFromFile( L"SimpleShader.fx", "PS", "ps_4_0", &d3dPixelShaderBlob );
	if(FAILED(hResult)) {
		MessageBox( NULL,
					L"No se pudo compilar shader.", L"Error", MB_OK );
		Game->Exit();
	}

	// Create the pixel shader
	hResult = Graphics->GetDevice()->CreatePixelShader( d3dPixelShaderBlob->GetBufferPointer(), d3dPixelShaderBlob->GetBufferSize(), NULL, &this->d3dPixelShader );
	d3dPixelShaderBlob->Release();
	if (FAILED(hResult))
		Game->Exit();

	// Create vertex buffer
	SimpleVertex a_sVertices[] =
	{
		{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ) },
		{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT4( 0.0f, 1.0f, 0.0f, 1.0f ) },
		{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT4( 0.0f, 1.0f, 1.0f, 1.0f ) },
		{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT4( 1.0f, 0.0f, 0.0f, 1.0f ) },
	};

	//Buffer Descriptor:
	//Configura un recurso, en este caso
	//un buffer de vertices e índices
	D3D11_BUFFER_DESC d3dBufferDescriptor;
	ZeroMemory( &d3dBufferDescriptor, sizeof(d3dBufferDescriptor) );

	//Lectura y escritura del buffer en el shader
	d3dBufferDescriptor.Usage = D3D11_USAGE_DEFAULT; 

	d3dBufferDescriptor.ByteWidth = sizeof( SimpleVertex ) * 4;
	d3dBufferDescriptor.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	d3dBufferDescriptor.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA d3dInitData;
	ZeroMemory( &d3dInitData, sizeof(d3dInitData) );
	d3dInitData.pSysMem = a_sVertices;
	hResult = Graphics->GetDevice()->CreateBuffer( &d3dBufferDescriptor, &d3dInitData, &this->d3dVertexBuffer );

	if( FAILED( hResult ) )
		Game->Exit();

	UINT uiStride = sizeof( SimpleVertex );
	UINT uiOffset = 0;
	Graphics->GetDeviceContext()->IASetVertexBuffers( 0, 1,  &this->d3dVertexBuffer, &uiStride, &uiOffset );

	// Creamos buffer de indices usando el mismo
	//descriptor
	WORD a_wIndices[] =
	{
		3,1,0,
		2,1,3,
		/*3,0,1,
		2,3,1,*/
	};

	d3dBufferDescriptor.Usage = D3D11_USAGE_DEFAULT;
	d3dBufferDescriptor.ByteWidth = sizeof( WORD ) * 12;        // 36 vertices needed for 12 triangles in a triangle list
	d3dBufferDescriptor.BindFlags = D3D11_BIND_INDEX_BUFFER;
	d3dBufferDescriptor.CPUAccessFlags = 0;
	d3dInitData.pSysMem = a_wIndices;
	hResult = Graphics->GetDevice()->CreateBuffer( &d3dBufferDescriptor, &d3dInitData, &this->d3dIndexBuffer );
	if( FAILED( hResult ) )
		Game->Exit();

	// Set index buffer
	Graphics->GetDeviceContext()->IASetIndexBuffer( this->d3dIndexBuffer, DXGI_FORMAT_R16_UINT, 0 );

	// Set topología de primitiva
	Graphics->GetDeviceContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	// Creamos el constant buffer
	d3dBufferDescriptor.Usage = D3D11_USAGE_DEFAULT;
	d3dBufferDescriptor.ByteWidth = sizeof(MatrixBuffer);
	d3dBufferDescriptor.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	d3dBufferDescriptor.CPUAccessFlags = 0;
	hResult = Graphics->GetDevice()->CreateBuffer( &d3dBufferDescriptor, NULL, &this->d3dConstantBuffer );
	if( FAILED( hResult ) )
		Game->Exit();

	this->mxWorld = XMMatrixIdentity();
}

CActorPlane::CActorPlane()
{
	this->OnLoad();
}

CActorPlane::~CActorPlane()
{

}

void CActorPlane::Update()
{
	static float fRotation;
	fRotation += .001f;
	this->mxWorld = XMMatrixRotationY( fRotation ) * XMMatrixRotationX( fRotation );
}

void CActorPlane::Draw()
{
	MatrixBuffer sMatrixBuffer;
	sMatrixBuffer.m_mxWorld = XMMatrixTranspose( this->mxWorld );
	sMatrixBuffer.m_mxView = XMMatrixTranspose( Camera->GetViewMatrix() );
	sMatrixBuffer.m_mxProjection = XMMatrixTranspose( Camera->GetProjectionMatrix() );
	Graphics->GetDeviceContext()->UpdateSubresource( this->d3dConstantBuffer, 0, NULL, &sMatrixBuffer, 0, 0 );

	//
	// Renderea un cubo
	//
	Graphics->GetDeviceContext()->VSSetShader( this->d3dVertexShader, NULL, 0 );
	Graphics->GetDeviceContext()->VSSetConstantBuffers( 0, 1, &this->d3dConstantBuffer );
	Graphics->GetDeviceContext()->PSSetShader( this->d3dPixelShader, NULL, 0 );
	Graphics->GetDeviceContext()->DrawIndexed( 12, 0, 0 );
}