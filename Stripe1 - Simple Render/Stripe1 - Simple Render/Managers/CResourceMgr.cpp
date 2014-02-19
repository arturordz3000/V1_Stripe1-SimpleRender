#include "../Game.h"

CResources::CResources()
{

}

CResources::~CResources()
{

}

CResourceMgr::CResourceMgr()
{
	ResourceMgr = this;
	iResourcesCount = 0;
}

CResourceMgr::~CResourceMgr()
{
	ResourceMgr = NULL;
}

void CResourceMgr::AddResources(CResources *pResources, unsigned int &iResourcesId)
{
	iResourcesId = iResourcesCount;
	lResources.push_back(pResources);
	iResourcesCount++;	
}

void CResourceMgr::LoadImageData(WCHAR* heightTex, BYTE** bHeightData, int &iImageWidth, int &iImageHeight, ID3D11Resource *d3dHeightMap)
{
	HRESULT resultado;
		D3DX11_IMAGE_INFO texInfo;
		resultado = D3DX11GetImageInfoFromFile(heightTex, NULL, &texInfo, NULL);

		D3DX11_IMAGE_LOAD_INFO texDesc;
		ZeroMemory(&texDesc, sizeof(texDesc));
		texDesc.CpuAccessFlags = D3D11_CPU_ACCESS_READ;
		texDesc.Usage = D3D11_USAGE_STAGING;
		texDesc.pSrcInfo = &texInfo;
		texDesc.Height = texInfo.Height;
		texDesc.Width = texInfo.Width;
		texDesc.Depth = texInfo.Depth;
		texDesc.Format = texInfo.Format;
		texDesc.Filter = D3DX11_FILTER_LINEAR;
		texDesc.MipLevels = texInfo.MipLevels;

		iImageWidth = (int)texInfo.Width;
		iImageHeight = (int)texInfo.Height;
		bHeightData = new BYTE*[iImageHeight];
		for( int i = 0 ; i < iImageWidth ; i++ )
			bHeightData[i] = new BYTE[iImageWidth];

		resultado = D3DX11CreateTextureFromFile(Graphics->GetDevice(), heightTex, &texDesc, NULL, &d3dHeightMap, NULL);

		D3D11_MAPPED_SUBRESOURCE subResrc;
		resultado = Graphics->GetDeviceContext()->Map(d3dHeightMap, 0, D3D11_MAP_READ, NULL, &subResrc);
		BYTE *pixel = reinterpret_cast<BYTE*>(subResrc.pData);

		for(UINT x = 0; x < iImageHeight; x++)
		{
			for(UINT y=0; y < iImageWidth; y++)
			{
				BYTE pPixel = pixel[(x * iImageWidth + y)*4];
				bHeightData[x][y] = pPixel/5;
			}
		}
		
		Graphics->GetDeviceContext()->Unmap(d3dHeightMap, 0);
}