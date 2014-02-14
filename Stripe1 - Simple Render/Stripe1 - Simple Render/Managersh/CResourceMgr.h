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

template<class VertexType, class IndexType, class ConstantType>
class CResourcesBuilder
{
public:

	CResourcesBuilder();
	~CResourcesBuilder();

	bool AddVertexShaderResource(WCHAR *wFileName, LPCSTR lstrEntryPoint, LPCSTR lstrShaderModel, 
		D3D11_INPUT_ELEMENT_DESC a_d3dLayout[], unsigned int uiNumLayoutParams);
	bool AddPixelShaderResource(WCHAR *wFileName, LPCSTR lstrEntryPoint, LPCSTR lstrShaderModel);
	bool AddVertexBuffer(VertexType vertexData[], unsigned int iSizeVertexData);
	bool AddIndexBuffer(IndexType indexData[], unsigned int iSizeIndexData);
	bool AddConstantBuffer(ConstantType constantData[], unsigned int iSizeConstantData);
	bool AddTexture(LPCWSTR lstrFileName);
	bool AddSampler(D3D11_FILTER d3d11Filter, D3D11_TEXTURE_ADDRESS_MODE d3d11AddressU, 
		D3D11_TEXTURE_ADDRESS_MODE d3d11AddressV, D3D11_TEXTURE_ADDRESS_MODE d3d11AddressW, float fMinLOD, float fMaxLOD);
	void Build(CResources *pResourcesOutput);

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

	void AddResources(CResources *pResources, int &iResourcesId);
	CResources* GetResourcesById(int &iResourcesId) { return lResources[iResourcesId]; }

private:
	int iResourcesCount;
	std::vector<CResources*> lResources;
};

#endif
