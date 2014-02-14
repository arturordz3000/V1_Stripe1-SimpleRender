#ifndef _CRESOURCEMGR_H_
#define _CRESOURCEMGR_H_

#include "../Game.h"
#include <vector>

class CResources
{
public:
	CResources();
	~CResources();

	ID3D11SamplerState* GetSampler() { return d3dSampler; }
	ID3D11ShaderResourceView* GetTexture() { return d3dTexture; }
	ID3D11VertexShader* GetVertexShader() { return d3dVertexShader; }
	ID3D11PixelShader* GetPixelShader() { return d3dPixelShader; }
	ID3D11InputLayout* GetInputLayout() { return d3dInputLayout; }
	ID3D11Buffer* GetVertexBuffer() { return d3dVertexBuffer; }
	ID3D11Buffer* GetIndexBuffer() { return d3dIndexBuffer; }
	ID3D11Buffer* GetConstantBuffer() { return d3dConstantBuffer; }

	void SetSampler(ID3D11SamplerState* d3dSampler) { this->d3dSampler = d3dSampler; }
	void SetTexture(ID3D11ShaderResourceView* d3dTexture) { this->d3dTexture = d3dTexture; }
	void SetVertexShader(ID3D11VertexShader* d3dVertexShader) { this->d3dVertexShader = d3dVertexShader; }
	void SetPixelShader(ID3D11PixelShader* d3dPixelShader) { this->d3dPixelShader = d3dPixelShader; }
	void SetInputLayout(ID3D11InputLayout* d3dInputLayout) { this->d3dInputLayout = d3dInputLayout; }
	void SetVertexBuffer(ID3D11Buffer* d3dVertexBuffer) { this->d3dVertexBuffer = d3dVertexBuffer; }
	void SetIndexBuffer(ID3D11Buffer* d3dIndexBuffer) { this->d3dIndexBuffer = d3dIndexBuffer; }
	void SetConstantBuffer(ID3D11Buffer* d3dConstantBuffer) { this->d3dConstantBuffer = d3dConstantBuffer; }

public:	
	ID3D11SamplerState* d3dSampler;
	ID3D11ShaderResourceView* d3dTexture;
	ID3D11VertexShader* d3dVertexShader;
	ID3D11PixelShader* d3dPixelShader;
	ID3D11InputLayout* d3dInputLayout;
	ID3D11Buffer* d3dVertexBuffer;
	ID3D11Buffer* d3dIndexBuffer;
	ID3D11Buffer* d3dConstantBuffer;
};

template<class VertexType, class IndexType, class ConstantType>
class CResourcesBuilder
{
public:

	CResourcesBuilder(){}
	~CResourcesBuilder(){}

	bool AddVertexShaderResource(WCHAR *wFileName, LPCSTR lstrEntryPoint, LPCSTR lstrShaderModel, 
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

	bool AddPixelShaderResource(WCHAR *wFileName, LPCSTR lstrEntryPoint, LPCSTR lstrShaderModel)
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

	bool AddVertexBuffer(VertexType vertexData[], unsigned int iSizeVertexData)
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
	bool AddIndexBuffer(IndexType indexData[], unsigned int iSizeIndexData)
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
	bool AddConstantBuffer(unsigned int iSizeConstantData)
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
	bool AddTexture(LPCWSTR lstrFileName)
	{
		HRESULT hResult = D3DX11CreateShaderResourceViewFromFile( Graphics->GetDevice(), lstrFileName, NULL, NULL, &this->d3dTexture, NULL );
		if( FAILED( hResult ) )
			return false;

		return true;
	}
	bool AddSampler(D3D11_FILTER d3d11Filter, D3D11_TEXTURE_ADDRESS_MODE d3d11AddressU, 
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
	void Build(CResources *pResourcesOutput)
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

private:
	ID3D11SamplerState* d3dSampler;
	ID3D11ShaderResourceView* d3dTexture;
	ID3D11VertexShader* d3dVertexShader;
	ID3D11PixelShader* d3dPixelShader;
	ID3D11InputLayout* d3dInputLayout;
	ID3D11Buffer* d3dVertexBuffer;
	ID3D11Buffer* d3dIndexBuffer;
	ID3D11Buffer* d3dConstantBuffer;
};

class CResourceMgr 
{
public:
	CResourceMgr();
	~CResourceMgr();

	void AddResources(CResources *pResources, unsigned int &iResourcesId);
	CResources* GetResourcesById(unsigned int &iResourcesId) { return lResources[iResourcesId]; }

private:
	unsigned int iResourcesCount;
	std::vector<CResources*> lResources;
};

#endif
