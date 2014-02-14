#include "../Game.h"

CResourceMgr::CResourceMgr()
{
	ResourceMgr = this;
	iResourcesCount = 0;
}

CResourceMgr::~CResourceMgr()
{
	ResourceMgr = NULL;
}

void CResourceMgr::AddResources(CResources *pResources, int &iResourcesId)
{
	iResourcesId = iResourcesCount;
	lResources.push_back(pResources);
	iResourcesCount++;	
}

CResourcesBuilder<class VertexType, class IndexType, class ConstantType>::CResourcesBuilder()
{

}

CResourcesBuilder<class VertexType, class IndexType, class ConstantType>::~CResourcesBuilder()
{

}

bool CResourcesBuilder<class VertexType, class IndexType, class ConstantType>::AddVertexShaderResource(WCHAR *wFileName, LPCSTR lstrEntryPoint, LPCSTR lstrShaderModel, 
		D3D11_INPUT_ELEMENT_DESC a_d3dLayout[], unsigned int uiNumLayoutParams)
{
	ID3DBlob* d3dVertexShaderBlob = NULL;
	HRESULT hResult = Graphics->CompileShaderFromFile(wFileName, lstrEntryPoint, lstrShaderModel, &d3dVertexShaderBlob);

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

	UINT numElements = uiNumLayoutParams;

	//Se crea el input layout
	hResult = Graphics->GetDevice()->CreateInputLayout( a_d3dLayout, numElements, d3dVertexShaderBlob->GetBufferPointer(),
		d3dVertexShaderBlob->GetBufferSize(), &this->d3dInputLayout );

	//Ya no se ocupará
	d3dVertexShaderBlob->Release();
	if(FAILED(hResult))
		return false;

	return true;
}

bool CResourcesBuilder<class VertexType, class IndexType, class ConstantType>::AddPixelShaderResource(WCHAR *wFileName, LPCSTR lstrEntryPoint, LPCSTR lstrShaderModel)
{
	ID3DBlob* d3dPixelShaderBlob = NULL;
	HRESULT hResult = Graphics->CompileShaderFromFile( wFileName, lstrEntryPoint, lstrShaderModel, &d3dPixelShaderBlob );
	if(FAILED(hResult)) {
		MessageBox( NULL,
					L"No se pudo compilar shader.", L"Error", MB_OK );
		Game->Exit();
	}

	// Create the pixel shader
	hResult = Graphics->GetDevice()->CreatePixelShader( d3dPixelShaderBlob->GetBufferPointer(), d3dPixelShaderBlob->GetBufferSize(), NULL, &this->d3dPixelShader );
	d3dPixelShaderBlob->Release();
	if (FAILED(hResult))
		return false;

	return true;
}

bool CResourcesBuilder<class VertexType, class IndexType, class ConstantType>::AddVertexBuffer(VertexType vertexData[], unsigned int iSizeVertexData)
{
	//Buffer Descriptor:
	//Configura un recurso, en este caso
	//un buffer de vertices e índices
	D3D11_BUFFER_DESC d3dBufferDescriptor;
	ZeroMemory( &d3dBufferDescriptor, sizeof(d3dBufferDescriptor) );

	//Lectura y escritura del buffer en el shader
	d3dBufferDescriptor.Usage = D3D11_USAGE_DEFAULT; 

	d3dBufferDescriptor.ByteWidth = iSizeVertexData;
	d3dBufferDescriptor.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	d3dBufferDescriptor.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA d3dInitData;
	ZeroMemory( &d3dInitData, sizeof(d3dInitData) );
	d3dInitData.pSysMem = vertexData;
	HRESULT hResult = Graphics->GetDevice()->CreateBuffer( &d3dBufferDescriptor, &d3dInitData, &this->d3dVertexBuffer );

	if( FAILED( hResult ) )
		return false;

	return true;
}

bool CResourcesBuilder<class VertexType, class IndexType, class ConstantType>::AddIndexBuffer(IndexType indexData[], unsigned int iSizeIndexData)
{
	//Buffer Descriptor:
	//Configura un recurso, en este caso
	//un buffer de vertices e índices
	D3D11_BUFFER_DESC d3dBufferDescriptor;
	ZeroMemory( &d3dBufferDescriptor, sizeof(d3dBufferDescriptor) );

	d3dBufferDescriptor.Usage = D3D11_USAGE_DEFAULT;
	d3dBufferDescriptor.ByteWidth = iSizeIndexData;        // 36 vertices needed for 12 triangles in a triangle list
	d3dBufferDescriptor.BindFlags = D3D11_BIND_INDEX_BUFFER;
	d3dBufferDescriptor.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA d3dInitData;
	ZeroMemory( &d3dInitData, sizeof(d3dInitData) );
	d3dInitData.pSysMem = indexData;
	HRESULT hResult = Graphics->GetDevice()->CreateBuffer( &d3dBufferDescriptor, &d3dInitData, &this->d3dIndexBuffer );
	if( FAILED( hResult ) )
		return false;

	return true;
}

bool CResourcesBuilder<class VertexType, class IndexType, class ConstantType>::AddConstantBuffer(ConstantType constantData[], unsigned int iSizeConstantData)
{
	//Buffer Descriptor:
	//Configura un recurso, en este caso
	//un buffer de vertices e índices
	D3D11_BUFFER_DESC d3dBufferDescriptor;
	ZeroMemory( &d3dBufferDescriptor, sizeof(d3dBufferDescriptor) );

	// Creamos el constant buffer
	d3dBufferDescriptor.Usage = D3D11_USAGE_DEFAULT;
	d3dBufferDescriptor.ByteWidth = sizeof(MatrixBuffer);
	d3dBufferDescriptor.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	d3dBufferDescriptor.CPUAccessFlags = 0;
	HRESULT hResult = Graphics->GetDevice()->CreateBuffer( &d3dBufferDescriptor, NULL, &this->d3dConstantBuffer );
	if( FAILED( hResult ) )
		return false;

	return true;
}

bool CResourcesBuilder<class VertexType, class IndexType, class ConstantType>::AddTexture(LPCWSTR lstrFileName)
{
	HRESULT hResult = D3DX11CreateShaderResourceViewFromFile( Graphics->GetDevice(), lstrFileName, NULL, NULL, &this->d3dTexture, NULL );
	if( FAILED( hResult ) )
		return false;

	return true;
}

bool CResourcesBuilder<class VertexType, class IndexType, class ConstantType>::AddSampler(D3D11_FILTER d3d11Filter, D3D11_TEXTURE_ADDRESS_MODE d3d11AddressU, 
		D3D11_TEXTURE_ADDRESS_MODE d3d11AddressV, D3D11_TEXTURE_ADDRESS_MODE d3d11AddressW, float fMinLOD, float fMaxLOD)
{
	// Creamos el sampler
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory( &sampDesc, sizeof(sampDesc) );
	//Filtro con interpolación lineal
	sampDesc.Filter = d3d11Filter;

	//Elige la forma en que tratará la textura si las coordenadas UV son mayores a 1.
	//D3D11_TEXTURE_ADDRESS_WRAP hace que se repita la textura. Cuando tenemos coordenas de 0 a 3, entonces
	//la textura se repetirá 3 veces
	sampDesc.AddressU = d3d11AddressU; 
	sampDesc.AddressV = d3d11AddressV;
	sampDesc.AddressW = d3d11AddressW;

	//LOD = Level of detail: Lower end of mipmap range, 0 es el máximo y más detallado
	sampDesc.MinLOD = fMinLOD; 

	//Como el mínimo se ha colocado como máximo, entonces no tenemos MaxLOD
	sampDesc.MaxLOD = fMaxLOD;

	HRESULT hResult = Graphics->GetDevice()->CreateSamplerState( &sampDesc, &this->d3dSampler );
	if( FAILED( hResult ) )
		return false;

	return true;
}

void CResourcesBuilder<class VertexType, class IndexType, class ConstantType>::Build(CResources *pResourcesOutput)
{
	pResourcesOutput->SetVertexShader(this->d3dVertexShader);
	pResourcesOutput->SetPixelShader(this->d3dPixelShader);
	pResourcesOutput->SetVertexBuffer(this->d3dVertexBuffer);
	pResourcesOutput->SetIndexBuffer(this->d3dIndexBuffer);
	pResourcesOutput->SetInputLayout(this->d3dInputLayout);
	pResourcesOutput->SetSampler(this->d3dSampler);
	pResourcesOutput->SetTexture(this->d3dTexture);
	pResourcesOutput->SetConstantBuffer(this->d3dConstantBuffer);
}